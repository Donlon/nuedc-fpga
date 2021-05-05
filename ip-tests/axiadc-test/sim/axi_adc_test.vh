
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

task axi_adc_bis_reg (
    input   bit [31:0]     offset,
    input   bit [31:0]     flags,
    output  xil_axi_resp_t resp
);
    axi_adc_read_reg(offset, data, resp);
    axi_adc_write_reg(offset, data | flags, resp);
endtask : axi_adc_bis_reg

task axi_adc_bic_reg (
    input   bit [31:0]     offset,
    input   bit [31:0]     flags,
    output  xil_axi_resp_t resp
);
    axi_adc_read_reg(offset, data, resp);
    axi_adc_write_reg(offset, data & ~flags, resp);
endtask : axi_adc_bic_reg

task axi_adc_wait_idle;
    bit busy;
    bit [31:0] rdata;
    xil_axi_resp_t resp;
    busy = 1;
    while (busy) begin
        axi_adc_read_reg(REG_CTL_INDEX, rdata, resp);
        busy = rdata[REG_CTL_BUSY_BIT];
        #100ns;
    end
endtask : axi_adc_wait_idle