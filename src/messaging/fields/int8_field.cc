#include <sstream>
#include "messaging/field.hh"
#include <iomanip>

void Int8Field::ParseFromStream(std::istream& stream) {
    auto name = ParseFieldName(stream);
    auto valueStr = ParseFieldStringValue(stream);
    uint8_t value = std::stoi(valueStr);

    name_ = name;
    value_ = value;
}

std::string Int8Field::DisplayValue() const {
    std::stringstream stream;
    stream << std::setw(NameLength) << std::left << name_ << " | " << +value_;
    return stream.str();
}

int Int8Field::SaveToBuffer(uint8_t* buffer, int offset) const {
    buffer[offset] = value_;
    return 1;
}

int Int8Field::SetValueFromBuffer(uint8_t* buffer, int offset) {
    value_ = buffer[offset];
    return 1;
}

