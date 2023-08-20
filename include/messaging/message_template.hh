#include <cstdint>
#include <iostream>
#include <vector>
#include <memory>
#include "field.hh"
#include <fstream>
#include <sstream>

class MessageTemplate {
public:
    MessageTemplate();
    ~MessageTemplate();
    int GetMessageLength();

    void ParseFile(const std::string& filePath);
    void Display();
    int SaveMessage(uint8_t* buffer);
    int SetValuesFromBuffer(uint8_t* buffer);

private:
    std::vector<std::unique_ptr<Field>> fields_;
    uint8_t* message_;
    int messageLength_ = 0;
};
