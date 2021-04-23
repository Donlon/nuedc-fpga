`timescale 1ns/100ps

module top_tb;
    reg clk_50M;
    wire gpio;
    
    top u_top(
        .clk_50M(clk_50M),
    
        .ext_reset_n(1),
        .gpio(gpio)
    );
    
    always #10 clk_50M = ~clk_50M;
    
    initial begin
        clk_50M = 0;
    end

    `define mem_size $size(u_top.u_ps_top.procesor_system_top_i.blk_mem_gen_0.inst.native_mem_mapped_module.blk_mem_gen_v8_4_3_inst.memory)
    reg [7:0]  temp_mem8  [0:`mem_size * 4 - 1];
    reg [31:0] temp_mem32 [0:`mem_size - 1];
    
    reg [31:0] i;
    initial begin
        for (i = 0; i < `mem_size * 4; i = i + 1) begin
            temp_mem8[i] = 0;
        end
        $readmemh("/home/donlon/Documents/eic/nuedc-fpga/cmake-build-debug-arm-gcc/eic-final/software/eic-final.hex", temp_mem8);

        // for (i = 0; i < `mem_size * 4; i = i + 1) begin
        //     if (temp_mem8[i][0] == 1'bx) begin
        //         temp_mem8[i] = 0;
        //     end
        // end
        for (i = 0; i < `mem_size; i = i + 1) begin
            temp_mem32[i] = {temp_mem8[i * 4 + 3], temp_mem8[i * 4 + 2], temp_mem8[i * 4 + 1], temp_mem8[i * 4]};
            // $display(" i = %d, loaded %0x", i, temp_mem32[i]);
        end

        u_top.u_ps_top.procesor_system_top_i.blk_mem_gen_0.inst.native_mem_mapped_module.blk_mem_gen_v8_4_3_inst.memory = temp_mem32;
        $display("top_tb: Block Memory Generator data initialization complete.");
    end
endmodule;