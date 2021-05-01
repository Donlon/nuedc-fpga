`timescale 1ns / 100ps

import axi_vip_pkg::*;
import axi_vip_1_axi_vip_m_0_pkg::*;
import axi_vip_1_axi_vip_s_0_pkg::*;

const int REG_CTL         = 32'h00;
const int REG_DATA        = 32'h04;
const int REG_SRC_ADDR    = 32'h08;
const int REG_SRC_SIZE    = 32'h0C;
const int REG_CLK_DIV     = 32'h10;

const int CTL_REG_REPEAT_BIT   = 'h00;
const int CTL_REG_LOOP_BIT     = 'h01;
const int CTL_REG_BUSY_BIT     = 'h02;
const int CTL_REG_START_BIT    = 'h03;
const int CTL_REG_STOP_BIT     = 'h04;

//////////////////////////////////////////////////////////////////////////////////
// Test Bench Signals
//////////////////////////////////////////////////////////////////////////////////

// Clock and Reset
bit aclk = 0, aresetn = 1;

// Simulation output
bit       dac_clk;
bit [7:0] dac_data;

//AXI4-Lite signals
xil_axi_resp_t  resp;
bit [31:0] addr, data, base_addr = 32'h4000_0000;

module tb_repeat_mode();
    wire       dac_clk;
    wire [7:0] dac_data;

    axi_vip_1_wrapper u_axi_vip(
        .aclk(aclk),
        .aresetn(aresetn),
        .dac_clk(dac_clk),
        .dac_data(dac_data)
    );

    // Generate the clock : 50 MHz
    always #10ns aclk = ~aclk;

    task axi_dac_read_reg (
        input   bit [31:0]     offset,
        output  bit [31:0]     data,
        output  xil_axi_resp_t resp
    );
        master_agent.AXI4LITE_READ_BURST(base_addr + offset, 0, data, resp);
    endtask : axi_dac_read_reg

    task axi_dac_write_reg (
        input   bit [31:0]     offset,
        input   bit [31:0]     data,
        output  xil_axi_resp_t resp
    );
        master_agent.AXI4LITE_WRITE_BURST(base_addr + offset, 0, data, resp);
    endtask : axi_dac_write_reg

    //////////////////////////////////////////////////////////////////////////////////
    // The following part controls the AXI VIP.
    // It follows the "Usefull Coding Guidelines and Examples" section from PG267
    //////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////
    // Main Process
    //////////////////////////////////////////////////////////////////////////////////
    initial begin
        // Assert the reset
        aresetn = 0;
        #50ns
        // Release the reset
        aresetn = 1;
    end

    // Step 3 - Declare the agent for the master VIP
    axi_vip_1_axi_vip_m_0_mst_t      master_agent;

    // Declare <component_name>_slv_mem_t for slave mem agent
    axi_vip_1_axi_vip_s_0_slv_mem_t  slave_agent;

    initial begin
        // Step 4 - Create a new agent
        master_agent = new("master vip agent", u_axi_vip.axi_vip_1_i.axi_vip_m.inst.IF);
        master_agent.start_master();
        slave_agent = new("slave vip mem agent", u_axi_vip.axi_vip_1_i.axi_vip_s.inst.IF); // agent is newed
        slave_agent.start_slave();                                                  //  agent starts to run
        slave_agent.mem_model.set_memory_fill_policy(XIL_AXI_MEMORY_FILL_RANDOM);
 
        $timeformat(-9, 2, " ns");
        // Wait for the reset to be released
        wait (aresetn == 1'b1);

        #50ns
        axi_dac_read_reg(REG_CTL, data, resp);
        axi_dac_write_reg(REG_SRC_ADDR, 32'h20000000, resp);
        axi_dac_write_reg(REG_SRC_SIZE, 16'd256, resp); // 4 * brust16
        axi_dac_write_reg(REG_CLK_DIV, 5, resp); // Clock div: 5
        #50ns
        axi_dac_write_reg(REG_CTL, data | (1 << CTL_REG_REPEAT_BIT) | (1 << CTL_REG_START_BIT), resp);

        wait (~u_axi_vip.axi_vip_1_i.axi_dac_0.inst.axi_dac_v0_1_S_AXI_inst.busy);
        $display("[%t] Repeat mode test ended.", $realtime);
        #1us $stop;

        axi_dac_write_reg(REG_SRC_SIZE, 16'd128, resp); // 2 * brust16
        axi_dac_write_reg(REG_CLK_DIV, 7, resp); // Clock div: 7

        axi_dac_read_reg(REG_CTL, data, resp);
        axi_dac_write_reg(REG_CTL,
                          data | (1 << CTL_REG_LOOP_BIT) | (1 << CTL_REG_START_BIT),
                          resp);
        #20us
        axi_dac_read_reg(REG_CTL, data, resp);
        axi_dac_write_reg(REG_CTL, data | (1 << CTL_REG_STOP_BIT), resp);
        $display("[%t] Stop signal was sent.", $realtime);

        wait (~u_axi_vip.axi_vip_1_i.axi_dac_0.inst.axi_dac_v0_1_S_AXI_inst.busy);
        $display("[%t] Loop mode test ended.", $realtime);
        #1us $stop;
    end

    //////////////////////////////////////////////////////////////////////////////////
    // Simulation output processes
    //////////////////////////////////////////////////////////////////////////////////

    always @(posedge dac_clk) begin
        $display("[DAC] dac value changed to 0x%x", dac_data);
    end
endmodule
