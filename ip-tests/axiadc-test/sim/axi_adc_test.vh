
task axi_adc_read_reg (
    input   bit [31:0]     offset,
    output  bit [31:0]     data,
    output  xil_axi_resp_t resp
);
    master_agent.AXI4LITE_READ_BURST(base_addr + offset, 0, data, resp);
endtask : axi_adc_read_reg

task axi_adc_write_reg (
    input   bit [31:0]     offset,
    input   bit [31:0]     data,
    output  xil_axi_resp_t resp
);
    master_agent.AXI4LITE_WRITE_BURST(base_addr + offset, 0, data, resp);
endtask : axi_adc_write_reg