/*
    dziesiętnie     8 4 -2 -1   bcd
    0               0000        0000
    1               0111        0001
    2               0110        0010
    3               0101        0011
    4               0100        0100
    5               1011        0101
    6               1010        0110
    7               1001        0111
    8               1000        1000
    9               1111        1001
*/

module conv(
    input [3:0] i,
    output logic [3:0] o
);
    always_comb
        case(i)
            4'b0000: o = 4'd0;
            4'b0111: o = 4'd1;
            4'b0110: o = 4'd2;
            4'b0101: o = 4'd3;
            4'b0100: o = 4'd4;
            4'b1011: o = 4'd5;
            4'b1010: o = 4'd6;
            4'b1001: o = 4'd7;
            4'b1000: o = 4'd8;
            4'b1111: o = 4'd9;
            default: o = 4'bx;
        endcase
endmodule
