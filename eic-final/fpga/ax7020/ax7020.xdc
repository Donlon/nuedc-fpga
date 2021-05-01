set_property CFGBVS VCCO [current_design]
set_property CONFIG_VOLTAGE 3.3 [current_design]

#####          clocks                 #####
set_property -dict {PACKAGE_PIN U18 IOSTANDARD LVCMOS33} [get_ports clk_50M]
create_clock -period 20.000 -name sys_clk_pin -add [get_ports clk_50M]
set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets TCK_IBUF]
#set_property CLOCK_DEDICATED_ROUTE FALSE [get_nets TCK_IBUF_BUFG]

#####          external reset pins    #####
set_property -dict {PACKAGE_PIN N15 IOSTANDARD LVCMOS33} [get_ports ext_reset_n]

#####          JTAG pins              #####
set_property -dict {PACKAGE_PIN K14 IOSTANDARD LVCMOS33} [get_ports TDO]
set_property -dict {PACKAGE_PIN J14 IOSTANDARD LVCMOS33} [get_ports TCK]
set_property -dict {PACKAGE_PIN H15 IOSTANDARD LVCMOS33} [get_ports TDI]
set_property -dict {PACKAGE_PIN G15 IOSTANDARD LVCMOS33} [get_ports TMS]

#####          GPIO pins              #####
set_property -dict {PACKAGE_PIN F17 IOSTANDARD LVCMOS33} [get_ports {gpio[15]}]
set_property -dict {PACKAGE_PIN F16 IOSTANDARD LVCMOS33} [get_ports {gpio[14]}]
set_property -dict {PACKAGE_PIN F20 IOSTANDARD LVCMOS33} [get_ports {gpio[13]}]
set_property -dict {PACKAGE_PIN F19 IOSTANDARD LVCMOS33} [get_ports {gpio[12]}]
set_property -dict {PACKAGE_PIN G20 IOSTANDARD LVCMOS33} [get_ports {gpio[11]}]
set_property -dict {PACKAGE_PIN G19 IOSTANDARD LVCMOS33} [get_ports {gpio[10]}]
set_property -dict {PACKAGE_PIN H18 IOSTANDARD LVCMOS33} [get_ports {gpio[9]}]
set_property -dict {PACKAGE_PIN L20 IOSTANDARD LVCMOS33} [get_ports {gpio[8]}]
set_property -dict {PACKAGE_PIN L19 IOSTANDARD LVCMOS33} [get_ports {gpio[7]}]
set_property -dict {PACKAGE_PIN M20 IOSTANDARD LVCMOS33} [get_ports {gpio[6]}]
set_property -dict {PACKAGE_PIN M19 IOSTANDARD LVCMOS33} [get_ports {gpio[5]}]

# KEY2
set_property -dict {PACKAGE_PIN N16 IOSTANDARD LVCMOS33} [get_ports {gpio[4]}]
# KEY3
set_property -dict {PACKAGE_PIN T17 IOSTANDARD LVCMOS33} [get_ports {gpio[3]}]
# KEY4
set_property -dict {PACKAGE_PIN R17 IOSTANDARD LVCMOS33} [get_ports {gpio[2]}]
# LED1
set_property -dict {PACKAGE_PIN M14 IOSTANDARD LVCMOS33} [get_ports {gpio[1]}]
# LED2
set_property -dict {PACKAGE_PIN M15 IOSTANDARD LVCMOS33} [get_ports {gpio[0]}]

#####          DAC pins              #####
set_property -dict {PACKAGE_PIN P18 IOSTANDARD LVCMOS33} [get_ports {dac_data[0]}]
set_property -dict {PACKAGE_PIN W14 IOSTANDARD LVCMOS33} [get_ports {dac_data[1]}]
set_property -dict {PACKAGE_PIN Y14 IOSTANDARD LVCMOS33} [get_ports {dac_data[2]}]
set_property -dict {PACKAGE_PIN V15 IOSTANDARD LVCMOS33} [get_ports {dac_data[3]}]
set_property -dict {PACKAGE_PIN W15 IOSTANDARD LVCMOS33} [get_ports {dac_data[4]}]
set_property -dict {PACKAGE_PIN Y16 IOSTANDARD LVCMOS33} [get_ports {dac_data[5]}]
set_property -dict {PACKAGE_PIN Y17 IOSTANDARD LVCMOS33} [get_ports {dac_data[6]}]
set_property -dict {PACKAGE_PIN P14 IOSTANDARD LVCMOS33} [get_ports {dac_data[7]}]
set_property -dict {PACKAGE_PIN R14 IOSTANDARD LVCMOS33} [get_ports {dac_clk}]


#####         SPI Configurate Setting        #######
# set_property BITSTREAM.CONFIG.SPI_BUSWIDTH 4 [current_design]
# set_property CONFIG_MODE SPIx4 [current_design]
# set_property BITSTREAM.CONFIG.CONFIGRATE 50 [current_design]
