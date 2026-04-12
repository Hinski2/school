module mul (
    output logic [9:0] o,
    input [7:0] a,
    input [1:0] sel
);
    logic [9:0] a1, a2, a3, a4;

    assign a1 = a;
    assign a2 = a << 1;
    assign a3 = a + (a << 1);
    assign a4 = a << 2;

    always_comb
        case (sel)
            2'd0: o = a1;
            2'd1: o = a2;
            2'd2: o = a3;
            2'd3: o = a4;
        endcase
endmodule
