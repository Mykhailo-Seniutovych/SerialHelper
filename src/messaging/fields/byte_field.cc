#include "messaging/field.hh"
#include <iomanip>
#include <iostream>

void ByteField::ParseFromStream(std::istream& stream) {
    auto name = ParseFieldName(stream);
    auto valueStr = ParseFieldStringValue(stream);

    int value;
    std::stringstream ss;
    ss << std::hex << valueStr;
    ss >> value;

    name_ = name;
    value_ = static_cast<uint8_t>(value);
}

std::string ByteField::DisplayValue() const {
    std::stringstream stream;
    stream << std::setw(NameLength) << std::left << name_ << " | " << std::hex << std::uppercase
           << static_cast<int>(value_);
    return stream.str();
}

int ByteField::SaveToBuffer(uint8_t* buffer, int offset) const {
    buffer[offset] = value_;
    return 1;
}

int ByteField::SetValueFromBuffer(uint8_t* buffer, int offset) {
    value_ = buffer[offset];
    return 1;
}

