#include <sstream>
#include "messaging/field.hh"
#include <iomanip>

void Int16Field::ParseFromStream(std::istream& stream) {
    auto name = ParseFieldName(stream);
    auto valueStr = ParseFieldStringValue(stream);
    uint16_t value = std::stoi(valueStr);

    name_ = name;
    value_ = value;
}

std::string Int16Field::DisplayValue() const {
    std::stringstream stream;
    stream << std::setw(NameLength) << std::left << name_ << " | " << value_;
    return stream.str();
}

int Int16Field::SaveToBuffer(uint8_t* buffer, int offset) const {
    buffer[offset] = static_cast<uint8_t>((value_ >> 8) & 0xFF);
    buffer[offset + 1] = static_cast<uint8_t>(value_ & 0xFF);
    return 2;
}

int Int16Field::SetValueFromBuffer(uint8_t* buffer, int offset) {
    // Int16 value will be stored in big endian order in the buffer
    value_ = (buffer[offset] << 8) | buffer[offset + 1];
    return 2;
}