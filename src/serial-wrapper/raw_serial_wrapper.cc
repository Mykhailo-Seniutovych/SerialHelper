#include <fcntl.h>
#include "serial-wrapper/raw_serial_wrapper.hh"
#include "termios.h"
#include <unistd.h>
#include <iostream>

RawSerialWrapper::RawSerialWrapper(SerialSettings settings) : settings_(std::move(settings)) {}

RawSerialWrapper::~RawSerialWrapper() {
    if (serialPort_) {
        close(serialPort_);
    }
}

void RawSerialWrapper::OpenConnection() {
    serialPort_ = open(settings_.serialPort.c_str(), O_RDWR);
    if (serialPort_ < 0) {
        std::cerr << "Cannot open serial connection, check that the serial device is connected to PC" << std::endl;
        exit(1);
    }

    struct termios tty = {};

    int operationResult = tcgetattr(serialPort_, &tty);
    if (operationResult != 0) {
        std::cerr << "Cannot get default serial connection params" << std::endl;
        exit(1);
    }

    tty.c_cflag &= ~PARENB; // Clear parity bit, disabling parity (most common)
    tty.c_cflag &= ~CSTOPB; // Clear stop field, only one stop bit used in communication (most common)
    tty.c_cflag &= ~CSIZE; // Clear all bits that set the data size
    tty.c_cflag |= CS8; // 8 bits per byte (most common)
    tty.c_cflag &= ~CRTSCTS; // Disable RTS/CTS hardware flow control (most common)
    tty.c_cflag |= CREAD | CLOCAL; // Turn on READ & ignore ctrl lines (CLOCAL = 1)

    tty.c_lflag &= ~ICANON;
    tty.c_lflag &= ~ECHO; // Disable echo
    tty.c_lflag &= ~ECHOE; // Disable erasure
    tty.c_lflag &= ~ECHONL; // Disable new-line echo
    tty.c_lflag &= ~ISIG; // Disable interpretation of INTR, QUIT and SUSP
    tty.c_iflag &= ~(IXON | IXOFF | IXANY); // Turn off s/w flow ctrl
    // Disable any special handling of received bytes
    tty.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);

    tty.c_oflag &= ~OPOST; // Prevent special interpretation of output bytes (e.g. newline chars)
    tty.c_oflag &= ~ONLCR; // Prevent conversion of newline to carriage return/line feed

    tty.c_cc[VTIME] = 255;    // Wait for up to 25.5s (255 deciseconds), returning as soon as any data is received.
    tty.c_cc[VMIN] = 0;

    auto baudRate = RawSerialWrapper::getBaudRate(settings_.baudRate);
    cfsetispeed(&tty, baudRate);
    cfsetospeed(&tty, baudRate);

    operationResult = tcsetattr(serialPort_, TCSANOW, &tty);
    if (operationResult != 0) {
        std::cerr << "Cannot set serial connection params" << std::endl;
        exit(1);
    }
}

speed_t RawSerialWrapper::getBaudRate(BaudRate baudRate) {
    switch (baudRate) {
        case BaudRate::BAUD_0:
            return B0;
        case BaudRate::BAUD_50:
            return B50;
        case BaudRate::BAUD_75:
            return B75;
        case BaudRate::BAUD_110:
            return B110;
        case BaudRate::BAUD_134:
            return B134;
        case BaudRate::BAUD_150:
            return B150;
        case BaudRate::BAUD_200:
            return B200;
        case BaudRate::BAUD_300:
            return B300;
        case BaudRate::BAUD_600:
            return B600;
        case BaudRate::BAUD_1200:
            return B1200;
        case BaudRate::BAUD_1800:
            return B1800;
        case BaudRate::BAUD_2400:
            return B2400;
        case BaudRate::BAUD_4800:
            return B4800;
        case BaudRate::BAUD_9600:
            return B9600;
        case BaudRate::BAUD_19200:
            return B19200;
        case BaudRate::BAUD_38400:
            return B38400;
        case BaudRate::BAUD_57600:
            return B57600;
        case BaudRate::BAUD_115200:
            return B115200;
        case BaudRate::BAUD_230400:
            return B230400;
        case BaudRate::BAUD_460800:
            return B460800;
        default:
            return B38400;
    }
}

void RawSerialWrapper::CloseConnection() {
    if (serialPort_) {
        close(serialPort_);
    }
}

std::uint8_t RawSerialWrapper::Read(std::uint8_t* buffer, int size) const {
    if (serialPort_ > 0) {
        return read(serialPort_, buffer, size);
    }
    return 0;
}

std::uint8_t RawSerialWrapper::Write(const std::uint8_t* buffer, int size) const {
    if (serialPort_ > 0) {
        return write(serialPort_, buffer, size);
    }
    return 0;
}

