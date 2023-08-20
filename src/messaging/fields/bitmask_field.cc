#include <cassert>
#include <sstream>
#include "messaging/field.hh"
#include <iomanip>
#include <unordered_map>

void BitMaskField::ParseFromStream(std::istream& stream) {
    std::stringstream charStream;
    char character;
    while (stream.get(character) && (character != '\r' && character != '\n')) {
        if (character != ' ') {
            charStream << character;
        }
    }
    auto fieldName = charStream.str();

    std::unordered_map<std::string, uint8_t> bitMap;

    std::vector<std::string> bitNames;
    uint8_t fieldValue = 0;
    int bitCounter = 0;
    while (true) {
        stream.get(character);
        if (character != ' ') {
            stream.seekg(-1, std::ios::cur);
            break;
        }

        while (stream.get(character) && character != ':') {
        }

        auto bitName = ParseFieldName(stream);
        auto bitValueStr = ParseFieldStringValue(stream);
        auto bitValue = std::stoi(bitValueStr);

        bitNames.push_back(bitName);
        fieldValue = fieldValue | (bitValue << bitCounter);
        ++bitCounter;
    }

    name_ = fieldName;
    value_ = fieldValue;
    bitNames_ = bitNames;
}

std::string BitMaskField::DisplayValue() const {
    std::stringstream stream;

    stream << name_;
    int bitNumber = 0;
    for (const auto& bitName : bitNames_) {
        int bitValue = (value_ >> bitNumber) & 1;
        stream << std::endl;
        stream << std::setw(NameLength) << std::left << "    " + bitName << " | " << bitValue;
        ++bitNumber;
    }

    return stream.str();
}

int BitMaskField::SaveToBuffer(uint8_t* buffer, int offset) const {
    buffer[offset] = value_;
    return 1;
}

int BitMaskField::SetValueFromBuffer(uint8_t* buffer, int offset) {
    value_ = buffer[offset];
    return 1;
}