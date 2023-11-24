#include <iostream>
#include <memory>
#include <thread>
#include <chrono>
#include "serial-wrapper/raw_serial_wrapper.hh"
#include "messaging/field.hh"
#include "messaging/message_template.hh"
#include "utils/crc16.hh"

static const std::string SerialPort = "/dev/ttyUSB0";
static const BaudRate BaudRate = BaudRate::BAUD_38400;
static const int SendIntervalMs = 100;

static std::unique_ptr<RawSerialWrapper> create_serial_wrapper();
[[noreturn]] static void run_serial_send_cycle(bool sendWithoutConfirmation);
[[noreturn]] static void run_serial_read_cycle();

int main(int argc, char** argv) {
    if (argc < 1 || std::string(argv[1]) == "--send") {
        auto sendWithoutConfirmation = argc > 2 && std::string(argv[2]) == "--no-ask";
        MessageTemplate requestMessage;
        run_serial_send_cycle(sendWithoutConfirmation);
    }

    if (std::string(argv[1]) == "--read") {
        run_serial_read_cycle();
    }

    return 0;
}

void run_serial_send_cycle(bool sendWithoutConfirmation) {
    auto serialWrapper = create_serial_wrapper();
    auto* buffer = new uint8_t[1024];
    MessageTemplate requestMessage;
    while (true) {
        requestMessage.ParseFile("files/request-template.txt");
        requestMessage.Display();
        int size = requestMessage.SaveMessage(buffer);

        if (!sendWithoutConfirmation) {
            std::string response;
            std::cout << "Press enter to send next" << std::endl;
            getline(std::cin, response);
            // Read again in case when file was edited when we were waiting for response
            requestMessage.ParseFile("files/request-template.txt");
            size = requestMessage.SaveMessage(buffer);
        }
        serialWrapper->Write(buffer, size);
        std::cout << "================================================================" << std::endl;

        if (sendWithoutConfirmation) {
            std::this_thread::sleep_for(std::chrono::milliseconds(SendIntervalMs));
        }
    }

    delete[] buffer;
}

void run_serial_read_cycle() {
    auto serialWrapper = create_serial_wrapper();
    auto* buffer = new uint8_t[1024];
    MessageTemplate responseMessage;
    while (true) {
        responseMessage.ParseFile("files/response-template.txt");
        int msgLength = responseMessage.GetMessageLength();

        int bytesRead = 0;
        while (bytesRead < msgLength) {
            bytesRead += serialWrapper->Read(buffer, msgLength);
        }

        auto actualCrcValue = buffer[msgLength - 2] | (buffer[msgLength - 1] << 8);
        auto expectedCrcValue = crc16_modbus_calculate(buffer, msgLength - 2);

        if (actualCrcValue == expectedCrcValue) {
            responseMessage.SetValuesFromBuffer(buffer);
            responseMessage.Display();
            std::cout << "================================================================" << std::endl;
        } else {
            // Uncomment to output error when CRC don't match
            //std::cout << "\033[1;31m" << "CRC VALUE DID NOT MATCH" << "\033[0m" << std::endl;
        }

    }
    delete[] buffer;
}

std::unique_ptr<RawSerialWrapper> create_serial_wrapper() {
    auto settings = SerialSettings{
            .serialPort = SerialPort,
            .baudRate = BaudRate
    };

    auto serialWrapper = std::make_unique<RawSerialWrapper>(settings);
    serialWrapper->OpenConnection();
    return serialWrapper;
}