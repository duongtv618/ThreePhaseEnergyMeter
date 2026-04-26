cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME 3PhaseEnergyMeter)

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})

# Include user defined configuration
include("${CMAKE_CURRENT_SOURCE_DIR}/local_config.cmake")

# Add STM32CubeMX generated sources
add_subdirectory(cmake/stm32cubemx)

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    "User/app/src/app.c"
    "User/app/src/adc_sample.c"
    "User/app/src/led_blink.c"
    "User/app/src/comm.c"
    "User/app/src/uart_dma.c"
    "User/lib/src/dsp.c"
    "User/lib/src/pll.c"
    "User/lib/src/calib.c"
    "User/mock/src/mock.c"
    "User/common/src/share_data.c"
    "User/sup/src/serial_plot.c"
    "User/common/src/ema.c"
    "User/lib/src/modbus_rtu.c"
    "User/lib/src/meter_register.c"
    "User/common/src/maf.c"
    "User/lib/src/mqtt.c"
)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    "User/app/inc"
    "User/lib/inc"
    "User/mock/inc"
    "User/common/inc"
    "User/sup/inc"
)

# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined symbols
)

# Remove wrong libob.a library dependency when using cpp files
list(REMOVE_ITEM CMAKE_C_IMPLICIT_LINK_LIBRARIES ob)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    stm32cubemx

    # Add user defined libraries
)
