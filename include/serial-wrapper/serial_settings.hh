#ifndef BCR_STM_INCLUDE_SERIAL_WRAPPER_SERIAL_SETTINGS_HH_
#define BCR_STM_INCLUDE_SERIAL_WRAPPER_SERIAL_SETTINGS_HH_

#include <string>

enum class BaudRate {
    BAUD_0,
    BAUD_50,
    BAUD_75,
    BAUD_110,
    BAUD_134,
    BAUD_150,
    BAUD_200,
    BAUD_300,
    BAUD_600,
    BAUD_1200,
    BAUD_1800,
    BAUD_2400,
    BAUD_4800,
    BAUD_9600,
    BAUD_19200,
    BAUD_38400,
    BAUD_57600,
    BAUD_115200,
    BAUD_230400,
    BAUD_460800
};

struct SerialSettings {
    std::string serialPort;
    BaudRate baudRate;
};


#endif //BCR_STM_INCLUDE_SERIAL_WRAPPER_SERIAL_SETTINGS_HH_
