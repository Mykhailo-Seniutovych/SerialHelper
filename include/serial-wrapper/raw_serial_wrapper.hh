#ifndef BCR_STM_INCLUDE_SERIAL_WRAPPER_RAW_SERIAL_WRAPPER_HH_
#define BCR_STM_INCLUDE_SERIAL_WRAPPER_RAW_SERIAL_WRAPPER_HH_
#include <termios.h>
#include "serial_wrapper.hh"


class RawSerialWrapper : public SerialWrapper {
public:
    explicit RawSerialWrapper(SerialSettings settings);
    ~RawSerialWrapper() override;
    void OpenConnection() override;
    void CloseConnection() override;
    std::uint8_t Read(std::uint8_t* buffer, int size) const override;
    std::uint8_t Write(const std::uint8_t* buffer, int size) const override;

private:
    SerialSettings settings_;
    int serialPort_ = 0;

    static speed_t getBaudRate(BaudRate baudRate);
};

#endif //BCR_STM_INCLUDE_SERIAL_WRAPPER_RAW_SERIAL_WRAPPER_HH_
