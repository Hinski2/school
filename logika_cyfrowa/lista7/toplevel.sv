module toplevel(input clk, input [15:0] d, input [1:0] sel,
                output logic [15:0] cnt, cmp, top, output out);
    assign out = cnt < cmp;

    always_ff @(posedge clk)
        if (sel == 2'b11) cnt <= d;
        else cnt <= cnt >= top ? 0 : cnt + 1;

    always_ff @(posedge clk)
        if(sel == 2'b01) cmp <= d;

    always_ff @(posedge clk)
        if(sel == 2'b10) top <= d;

endmodule
