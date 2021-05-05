`timescale 1ns / 100ps

import axi_vip_pkg::*;
import axi_vip_1_axi_vip_m_0_pkg::*;
import axi_vip_1_axi_vip_s_0_pkg::*;

//////////////////////////////////////////////////////////////////////////////////
// Test Bench Signals
//////////////////////////////////////////////////////////////////////////////////

// Clock and Reset
bit aclk = 0, aresetn = 1;

//AXI4-Lite signals
xil_axi_resp_t resp;
bit [31:0] addr, data, base_addr = 'h40000000;

module tb_repeat_conv();
    `include "axi_adc.vh"
    `include "axi_adc_test.vh"

    wire       adc_clk;
    reg  [7:0] adc_data;

    axi_vip_1_wrapper u_axi_vip(
        .aclk(aclk),
        .aresetn(aresetn),
        .adc_clk(adc_clk),
        .adc_data(adc_data)
    );

    // Generate the clock : 50 MHz
    always #10ns aclk = ~aclk;

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
        #400ns
        // Release the reset
        aresetn = 1;
    end

    // Step 3 - Declare the agent for the master VIP
    axi_vip_1_axi_vip_m_0_mst_t      master_agent;
    axi_vip_1_axi_vip_s_0_slv_mem_t  slave_agent;

    initial begin
        master_agent = new("master vip agent", u_axi_vip.axi_vip_1_i.axi_vip_m.inst.IF);
        master_agent.start_master();
        slave_agent = new("slave vip mem agent", u_axi_vip.axi_vip_1_i.axi_vip_s.inst.IF);
        slave_agent.start_slave();
        slave_agent.mem_model.set_memory_fill_policy(XIL_AXI_MEMORY_FILL_RANDOM);

        $timeformat(-9, 2, " ns");

        // Wait for the reset to be released
        wait (aresetn == 1'b1);

        #50ns
        axi_adc_read_reg(REG_CTL, data, resp);

        // ================ div=3, repeat ================
        axi_adc_write_reg(REG_CLK_DIV,  'd3, resp);
        axi_adc_write_reg(REG_DST_ADDR, 'h20000000, resp);
        axi_adc_write_reg(REG_DST_SIZE, 'd256, resp);
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_REPEAT_BIT) | (1 << REG_CTL_START_BIT), resp);
        axi_adc_wait_idle();
        #1us
        $display("[%t] Repeat mode test 1 finished.", $realtime);
        $stop();

        // ================ div=1, repeat ================
        axi_adc_write_reg(REG_CLK_DIV, 'd1, resp);
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_START_BIT), resp);
        #5us
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_STOP_BIT), resp);
        axi_adc_wait_idle();
        #1us
        $display("[%t] Repeat mode test 2 finished.", $realtime);
        $stop();

        // ================ div=7, repeat ================
        axi_adc_write_reg(REG_CLK_DIV,  'd7, resp);
        axi_adc_write_reg(REG_DST_SIZE, 'd55, resp);
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_START_BIT), resp);
        axi_adc_wait_idle();
        #1us
        $display("[%t] Repeat mode test 3 finished.", $realtime);
        $stop();


        // ================ div=7, repeat ================
        axi_adc_write_reg(REG_CLK_DIV,  'd6, resp);
        axi_adc_write_reg(REG_DST_SIZE, 'd55, resp);
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_START_BIT), resp);
        #3us
        axi_adc_bis_reg(REG_CTL, (1 << REG_CTL_STOP_BIT), resp);
        axi_adc_wait_idle();
        #1us
        $display("[%t] Repeat mode test 3 finished.", $realtime);
        $stop();

    end

    //////////////////////////////////////////////////////////////////////////////////
    // Simulation output processes
    //////////////////////////////////////////////////////////////////////////////////

    always @(posedge adc_clk) begin
        // $display("[DAC] dac value changed to 0x%x", dac_data);
        adc_data = $urandom();
    end
endmodule

