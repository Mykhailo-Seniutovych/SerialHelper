#include "utils/crc16.hh"
#include "messaging/field.hh"
#include <iomanip>
#include <iostream>

Crc16Field::Crc16Field(uint8_t* message, uint16_t messageLength) {
    value_ = crc16_modbus_calculate(message, messageLength);
}

void Crc16Field::ParseFromStream(std::istream& stream) {
    auto name = ParseFieldName(stream);
    name_ = name;
}

std::string Crc16Field::DisplayValue() const {
    std::stringstream stream;
    stream << std::setw(NameLength) << std::left << name_ << " | " << value_;
    return stream.str();
}

int Crc16Field::SaveToBuffer(uint8_t* buffer, int offset) const {
    // CRC value will be written in little endian order
    buffer[offset] = static_cast<uint8_t>(value_ & 0xFF);
    buffer[offset + 1] = static_cast<uint8_t>((value_ >> 8) & 0xFF);
    return 2;
}

int Crc16Field::SetValueFromBuffer(uint8_t* buffer, int offset) {
    // CRC value will be interpreted in little endian order
    value_ = buffer[offset] | (buffer[offset + 1] << 8);
    return 2;
}