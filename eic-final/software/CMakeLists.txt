
set(BSP_DIRECTORY "${PROJECT_SOURCE_DIR}/eic-final/bsp/standalone_bsp_0/CORTEXM3_AXI_0/")

add_executable(eic-final
        main.c startup.c sys_irq_handlers.c)

target_include_directories(eic-final PRIVATE ${BSP_DIRECTORY}/include)
target_include_directories(eic-final PRIVATE CMSIS/Include)
target_include_directories(eic-final PRIVATE CMSIS/Device/Include)

target_link_libraries(eic-final PRIVATE eic_final_bsp)

target_link_options(eic-final PRIVATE
        --specs=nano.specs
        -T ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds
        -Wall
        -Wextra
        )
set_target_properties(eic-final PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds)

add_custom_command(
        TARGET eic-final
        POST_BUILD
        COMMAND ${CMAKE_OBJCOPY} -O verilog $<TARGET_FILE:eic-final> ${CMAKE_CURRENT_BINARY_DIR}/eic-final.hex
        BYPRODUCTS ${CMAKE_CURRENT_BINARY_DIR}/eic-final.hex
        WORKING_DIRECTORY $<TARGET_FILE_DIR:eic-final>
        VERBATIM)