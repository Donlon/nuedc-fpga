
set(BSP_DIRECTORY "${PROJECT_SOURCE_DIR}/eic-final/bsp/standalone_bsp_0/CORTEXM3_AXI_0/")

add_executable(dac-swtest
        main.c startup.c sys_irq_handlers.c)

target_include_directories(dac-swtest PRIVATE ${BSP_DIRECTORY}/include)
target_include_directories(dac-swtest PRIVATE CMSIS/Include)
target_include_directories(dac-swtest PRIVATE CMSIS/Device/Include)

target_link_directories(dac-swtest PRIVATE ${BSP_DIRECTORY}/lib)
target_link_libraries(dac-swtest PRIVATE m xil)

target_link_options(dac-swtest PRIVATE
        --specs=nano.specs
        -T ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds
        -Wall
        -Wextra
        )
set_target_properties(dac-swtest PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds)

add_custom_command(
        TARGET dac-swtest
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O verilog $<TARGET_FILE:dac-swtest> ${CMAKE_CURRENT_BINARY_DIR}/dac-swtest.hex
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/dac-swtest.hex
        WORKING_DIRECTORY $<TARGET_FILE_DIR:dac-swtest>
        VERBATIM)