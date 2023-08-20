#ifndef BCR_STM_INCLUDE_MESSAGING_FIELDS_FIELD_HH_
#define BCR_STM_INCLUDE_MESSAGING_FIELDS_FIELD_HH_
#include <vector>
#include <string>

const int NameLength = 25;

class Field {
public:
    virtual void ParseFromStream(std::istream& stream) = 0;
    virtual int SetValueFromBuffer(uint8_t* buffer, int offset) = 0;
    [[nodiscard]]
    virtual std::string DisplayValue() const = 0;
    virtual int SaveToBuffer(uint8_t* buffer, int offset) const = 0;

    virtual ~Field() = default;
protected:
    static std::string ParseFieldName(std::istream& stream);
    static std::string ParseFieldStringValue(std::istream& stream);
};

class ByteField : public Field {
public:
    void ParseFromStream(std::istream& stream) override;
    int SetValueFromBuffer(uint8_t* buffer, int offset) override;
    [[nodiscard]]
    std::string DisplayValue() const override;
    int SaveToBuffer(uint8_t* buffer, int offset) const override;
private:
    std::string name_;
    uint8_t value_;
};

class Int8Field : public Field {
public:
    void ParseFromStream(std::istream& stream) override;
    int SetValueFromBuffer(uint8_t* buffer, int offset) override;
    [[nodiscard]]
    std::string DisplayValue() const override;
    int SaveToBuffer(uint8_t* buffer, int offset) const override;

private:
    std::string name_;
    uint8_t value_;
};

class Int16Field : public Field {
public:
    void ParseFromStream(std::istream& stream) override;
    int SetValueFromBuffer(uint8_t* buffer, int offset) override;
    [[nodiscard]]
    std::string DisplayValue() const override;
    int SaveToBuffer(uint8_t* buffer, int offset) const override;

private:
    std::string name_;
    uint16_t value_;
};

class BitMaskField : public Field {
public:
    void ParseFromStream(std::istream& stream) override;
    int SetValueFromBuffer(uint8_t* buffer, int offset) override;
    [[nodiscard]]
    std::string DisplayValue() const override;
    int SaveToBuffer(uint8_t* buffer, int offset) const override;

private:
    std::string name_;
    std::vector<std::string> bitNames_;
    uint8_t value_;
};

class Crc16Field : public Field {
public:
    Crc16Field(uint8_t* message, uint16_t messageLength);

    void ParseFromStream(std::istream& stream) override;
    int SetValueFromBuffer(uint8_t* buffer, int offset) override;
    [[nodiscard]]
    std::string DisplayValue() const override;
    int SaveToBuffer(uint8_t* buffer, int offset) const override;

private:
    std::string name_;
    uint16_t value_;
};

#endif //BCR_STM_INCLUDE_MESSAGING_FIELDS_FIELD_HH_
