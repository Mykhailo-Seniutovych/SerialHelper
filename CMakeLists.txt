set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_VERSION 1)
cmake_minimum_required(VERSION 3.16)

project(bcr_stm
        VERSION 0.1.0
        DESCRIPTION "A small program that automate some tasks for reading/writing serial data in Linux"
        LANGUAGES CXX)

set(CMAKE_CXX_COMPILER g++)
set(CMAKE_CXX_STANDARD 17)

set(SOURCES
        src/main.cc
        src/utils/crc16.cc
        src/serial-wrapper/raw_serial_wrapper.cc
        src/messaging/fields/byte_field.cc
        src/messaging/fields/int8_field.cc
        src/messaging/fields/int16_field.cc
        src/messaging/fields/crc16_field.cc
        src/messaging/fields/bitmask_field.cc
        src/messaging/fields/field.cc
        src/messaging/message_template.cc)
set(TARGET serial-helper)

add_compile_options(-Werror=return-type)

add_executable(${TARGET} ${SOURCES})
target_include_directories(${TARGET} PRIVATE include)

configure_file(files/request-template.txt files/request-template.txt COPYONLY)
configure_file(files/response-template.txt files/response-template.txt COPYONLY)
