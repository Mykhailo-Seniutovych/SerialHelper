#include <iostream>
#include <chrono>
#include <thread>
#include "messaging/field.hh"
#include "messaging/message_template.hh"
#include "utils/crc16.hh"

int main(int argc, char** argv) {
    if (argc < 1 || std::string(argv[1]) == "--send") {
        MessageTemplate requestMessage;
        while (true) {
            requestMessage.ParseFile("files/request-template.txt");
            requestMessage.Display();
            uint8_t buffer[256] = {0};
            requestMessage.SaveMessage(buffer);

            if (argc > 2 && std::string(argv[1]) == "--no-ask") {
                continue;
            }

            std::string response;
            std::cout << "Press enter to send next" << std::endl;
            getline(std::cin, response);
            std::cout << "================================================================" << std::endl;
        }
    }

    if (std::string(argv[1]) == "--read") {
        MessageTemplate responseMessage;
        while (true) {
            responseMessage.ParseFile("files/response-template.txt");

            uint8_t responseBuffer[38] = {
                    0xA8, 0x26, 0x02, 0x02, 0xFA, 0x64, 0xC8, 0x0E, 0x17, 0xDE, 0x3F, 0xFA, 0x04, 0xD2, 0x04, 0xD3,
                    0x04, 0xD4,
                    0x04, 0xD5, 0x04, 0xD6, 0x04, 0xD7, 0x04, 0xD8, 0x04, 0xD9, 0x04, 0xDA, 0x04, 0xDB, 0x04, 0xDC,
                    0x04, 0xDD,
                    0x3F, 0xD0
            };
            responseBuffer[34] = rand() % 32000;

            responseMessage.SetValuesFromBuffer(responseBuffer);
            responseMessage.Display();
            std::cout << "================================================================" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
    }

    return 0;
}
