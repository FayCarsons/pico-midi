cmake_minimum_required(VERSION 3.13)

# initialize the SDK based on PICO_SDK_PATH
# note: this must happen before project()
include(pico_sdk_import.cmake)

project(pmidi)

# initialize the Raspberry Pi Pico SDK
pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.cpp
)

# Add pico_stdlib library which aggregates commonly used features
target_link_libraries(${PROJECT_NAME} 
                pico_stdlib
                hardware_i2c)

# create map/bin/hex/uf2 file in addition to ELF.
pico_add_extra_outputs(pmidi)
pico_enable_stdio_usb(pmidi 1)
pico_enable_stdio_uart(pmidi 0)