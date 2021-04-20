cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_FLAGS "--specs=nosys.specs -mcpu=cortex-m3 -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions")

if (${GNU_TOOLCHAIN_PATH})
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_C_COMPILER_WORKS 1)
    set(CMAKE_CXX_COMPILER_WORKS 1)
    set(CMAKE_C_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_CXX_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-g++${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_ASM_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_AR ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ar${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_OBJCOPY ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-objcopy${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_OBJDUMP ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-objdump${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_LINKER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ld${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_RANLIB ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ranlib${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_SIZE ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-size${CMAKE_EXECUTABLE_SUFFIX})
    set(CMAKE_STRIP ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-strip${CMAKE_EXECUTABLE_SUFFIX})
endif ()

project(nuedc-fpga C)

add_subdirectory(eic-final/software)