#include "messaging/message_template.hh"
#include "utils/crc16.hh"

MessageTemplate::MessageTemplate() {
    const int maxMessageSize = 1024;
    message_ = new uint8_t[maxMessageSize];
}

MessageTemplate::~MessageTemplate() {
    delete[] message_;
}

int MessageTemplate::GetMessageLength() {
    return messageLength_;
}

void MessageTemplate::ParseFile(const std::string& filePath) {
    fields_.clear();
    messageLength_ = 0;

    std::ifstream requestFile(filePath);
    if (!requestFile.is_open())
        return;

    while (true) {
        std::stringstream charStream;
        char character;
        while (requestFile.get(character) && character != ':') {
            charStream << character;
        }
        if (requestFile.eof())
            break;

        auto fieldType = charStream.str();

        std::unique_ptr<Field> field;
        if (fieldType == "hex") {
            field = std::make_unique<ByteField>();
        } else if (fieldType == "int8") {
            field = std::make_unique<Int8Field>();
        } else if (fieldType == "int16") {
            field = std::make_unique<Int16Field>();
        } else if (fieldType == "bitmask") {
            field = std::make_unique<BitMaskField>();
        } else if (fieldType == "crc16") {
            field = std::make_unique<Crc16Field>(message_, messageLength_);
        } else {
            std::cerr << "Cannot parse unknown type " << fieldType << std::endl;
            exit(1);
        }
        field->ParseFromStream(requestFile);
        auto bytesWritten = field->SaveToBuffer(message_, messageLength_);
        messageLength_ += bytesWritten;
        fields_.push_back(std::move(field));
    }

}

void MessageTemplate::Display() {
    for (auto& field : fields_) {
        std::cout << field->DisplayValue() << std::endl;
    }
}

int MessageTemplate::SaveMessage(uint8_t* buffer) {
    for (int i = 0; i < messageLength_; ++i) {
        buffer[i] = message_[i];
    }
    return messageLength_;
}

int MessageTemplate::SetValuesFromBuffer(uint8_t* buffer) {
    int bytesRead = 0;
    for (auto& field : fields_) {
        bytesRead += field->SetValueFromBuffer(buffer, bytesRead);
    }
    return bytesRead;
}
