#ifndef BCR_STM_SRC_SERIAL_WRAPPER_HH_
#define BCR_STM_SRC_SERIAL_WRAPPER_HH_
#include "serial_settings.hh"
#include <cstdint>

class SerialWrapper {
public:
    virtual ~SerialWrapper() {};
    virtual void OpenConnection() = 0;
    virtual void CloseConnection() = 0;
    virtual std::uint8_t Read(std::uint8_t* buffer, int size) const = 0;
    virtual std::uint8_t Write(const std::uint8_t* buffer, int size) const = 0;
};

#endif //BCR_STM_SRC_SERIAL_WRAPPER_HH_
