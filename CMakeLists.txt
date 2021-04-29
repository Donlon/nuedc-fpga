cmake_minimum_required(VERSION 3.17)

set(CMAKE_C_FLAGS "--specs=nosys.specs -mcpu=cortex-m3 -Wall -Wextra -g")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS} -fno-exceptions")

# Toolchain settings
if (DEFINED GNU_TOOLCHAIN_PATH)
    message("Toolchain path: ${GNU_TOOLCHAIN_PATH}")
    set(CMAKE_SYSTEM_NAME Generic)
    set(CMAKE_C_COMPILER_WORKS 1)
    set(CMAKE_CXX_COMPILER_WORKS 1)
    if (WIN32)
        set(EXECUTABLE_SUFFIX ".exe")
    endif ()
    set(CMAKE_C_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc${EXECUTABLE_SUFFIX})
    set(CMAKE_CXX_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-g++${EXECUTABLE_SUFFIX})
    set(CMAKE_ASM_COMPILER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-gcc${EXECUTABLE_SUFFIX})
    set(CMAKE_AR ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ar${EXECUTABLE_SUFFIX})
    set(CMAKE_OBJCOPY ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-objcopy${EXECUTABLE_SUFFIX})
    set(CMAKE_OBJDUMP ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-objdump${EXECUTABLE_SUFFIX})
    set(CMAKE_LINKER ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ld${EXECUTABLE_SUFFIX})
    set(CMAKE_RANLIB ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-ranlib${EXECUTABLE_SUFFIX})
    set(CMAKE_SIZE ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-size${EXECUTABLE_SUFFIX})
    set(CMAKE_STRIP ${GNU_TOOLCHAIN_PATH}/bin/arm-none-eabi-strip${EXECUTABLE_SUFFIX})
endif ()

project(nuedc-fpga C)

add_subdirectory(eic-final/software)

add_subdirectory(ip-tests/dac-swtest)