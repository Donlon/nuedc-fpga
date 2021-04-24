`timescale 1ns / 100ps

import axi_vip_pkg::*;
import axi_vip_1_axi_vip_m_0_pkg::*;
// AXI_GPIO_Sim  axi_vip_0_0_pkg

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
bit[31:0]  addr, data, base_addr = 32'h4000_0000, switch_state;

module tb_single_conv();
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

    //////////////////////////////////////////////////////////////////////////////////
    // Main Process
    //////////////////////////////////////////////////////////////////////////////////
    //
    initial begin
        //Assert the reset
        aresetn = 0;
        #200ns
        // Release the reset
        aresetn = 1;
    end
    //
    //////////////////////////////////////////////////////////////////////////////////
    // The following part controls the AXI VIP. 
    //It follows the "Usefull Coding Guidelines and Examples" section from PG267
    //////////////////////////////////////////////////////////////////////////////////
    //
    // Step 3 - Declare the agent for the master VIP
    axi_vip_1_axi_vip_m_0_mst_t      master_agent;
    //
    initial begin    

        // Step 4 - Create a new agent
        master_agent = new("master vip agent",u_axi_vip.axi_vip_1_i.axi_vip_m.inst.IF);
        
        // Step 5 - Start the agent
        master_agent.start_master();
        
        //Wait for the reset to be released
        wait (aresetn == 1'b1);
        
        //Send 0x1 to the AXI GPIO Data register 1
        #500ns
        addr = 0;
        data = 1;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);
        
        //Send 0x0 to the AXI GPIO Data register 1
        #200ns
        addr = 0;
        data = 0;
        master_agent.AXI4LITE_WRITE_BURST(base_addr + addr, 0, data, resp);

        // // Switch in OFF position
        // switch_1 = 0;
        // Read the AXI GPIO Data register 2
        #200ns
        addr = 8;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr, 0, data, resp);
        switch_state = data&1'h1;
        if(switch_state == 0)
            $display("switch 1 OFF");
        else
            $display("switch 1 ON");
         
        // // Switch in ON position
        // switch_1 = 1;
        // Read the AXI GPIO Data register 2
        #200ns
        addr = 8;
        master_agent.AXI4LITE_READ_BURST(base_addr + addr, 0, data, resp);
        switch_state = data&1'h1;
        if(switch_state == 0)
            $display("switch 1 OFF");
        else
            $display("switch 1 ON"); 
            
    end
    //
    //////////////////////////////////////////////////////////////////////////////////
    // Simulation output processes
    //////////////////////////////////////////////////////////////////////////////////
    //
    always @(posedge dac_clk) begin
         $display("dac value changed to %d", dac_data);
    end
endmodule
