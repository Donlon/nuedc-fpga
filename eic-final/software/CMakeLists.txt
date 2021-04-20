
set(BSP_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/../bsp")

add_executable(eic-final
        main.c startup.c sys_irq_handlers.c)

target_include_directories(eic-final PRIVATE ${BSP_DIRECTORY}/CORTEXM3_AXI_0/include)
target_include_directories(eic-final PRIVATE CMSIS/Include)
target_include_directories(eic-final PRIVATE CMSIS/Device/Include)

target_link_directories(eic-final PRIVATE ${BSP_DIRECTORY}/CORTEXM3_AXI_0/lib)
target_link_libraries(eic-final PRIVATE xil)

target_link_options(eic-final PRIVATE
        --specs=nano.specs
        -T ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds
        -Wall
        -Wextra
        )
set_target_properties(eic-final PROPERTIES LINK_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cm3soc.lds)
