#include <sstream>
#include "messaging/field.hh"

std::string Field::ParseFieldName(std::istream& stream) {
    std::stringstream charStream;
    char character;
    while (stream.get(character) && character != ' ') {
        charStream << character;
    }
    while (stream.get(character) && character != '|') {
    }

    return charStream.str();
}

std::string Field::ParseFieldStringValue(std::istream& stream) {
    std::stringstream charStream;
    char character;
    while (stream.get(character) && character == ' ') {
    }
    charStream << character;

    while (stream.get(character) && (character != '\n')) {
        if (character != ' ' && character != '\r' && character != '\n') {
            charStream << character;
        }
    }

    return charStream.str();
}