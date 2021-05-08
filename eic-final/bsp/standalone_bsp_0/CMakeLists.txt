file(GLOB_RECURSE eic_final_bsp_sources CORTEXM3_AXI_0/libsrc/*.c)

add_library(eic_final_bsp ${eic_final_bsp_sources})
target_include_directories(eic_final_bsp PRIVATE CORTEXM3_AXI_0/include)
