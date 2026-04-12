// dekoder 3->8 z wykorzystaniem 2 instancji dekodera 2->4 z wejściem aktywującym

module dec2to4(
    input [1:0] i,
    input en,
    output [3:0] o
);
    assign o = en ? (4'b1 << i) : 4'b0;
endmodule

module dec3to8(
    input [2:0] i,
    output [7:0] o
);
    dec2to4 lo(i[1:0], ~i[2], o[3:0]);  // gdy i[2] == 0
    dec2to4 hi(i[1:0], i[2], o[7:4]);   // gdy i[2] == 1
endmodule

