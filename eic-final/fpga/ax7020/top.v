module top(
    input ext_clk,

    input ext_reset_n,
    inout [15:0] gpio,

    input  uart_rxd,
    output uart_txd,

    // JTAG pins
    input  TCK,
    input  TMS,
    input  TDI,
    output TDO,
    
    output [7:0] dac_data,
    output       dac_clk
);
    wire mclk;
    wire clk_150M;
    wire clk_locked;
    wire TDOEN_n;

    main_mmcm u_mmcm(
        // Clock out ports
        .clk_50M(mclk),       // output clk_50M
        .clk_150M(clk_150M),    // output clk_16M
        // Status and control signals
        .locked(clk_locked),  // output locked
        // Clock in ports
        .clk_in_50M(ext_clk)
    );

    procesor_system_top_wrapper u_ps_top(
        .mclk(mclk),
        .hclk(clk_150M),

        // JTAG pins
        .SWCLKTCK(TCK),
        .SWDITMS(TMS),
        .SWDO(SWDO),
        .TDI(TDI),
        .TDO(TDO),
        .SWDOEN(),
        .TDOEN_n(TDOEN_n),

        .clk_locked(clk_locked),
        .ext_reset_n(ext_reset_n),
        .gpio_tri_io(gpio),
        .uart_rxd(uart_rxd),
        .uart_txd(uart_txd),
        
        .dac_clk(dac_clk),
        .dac_data(dac_data)
    );
endmodule
