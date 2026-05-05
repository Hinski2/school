// dff z wykładu
module dff(output q, nq, input clk, d);
    logic r, s, nr, ns;
    nand gq (q,  nr, nq), gnq(nq, ns, q),
            gr (nr, clk, r), gs (ns, nr, clk, s),
            gr1(r,  nr, s), gs1(s,  ns, d);
endmodule

/*
    3 - load
    2 - >> 
    1 - << 
    0 - hold
*/
module mux(input [3:0] i, input [1:0] s, output o);
    assign o = s[1] ? (s[0] ? i[3] : i[2]) : (s[0] ? i[1] : i[0]);
endmodule

module toplevel(input [7:0] d, input i, c, l, r, output [7:0] q);
    wire [1:0] s = {l, r};
    logic [7:0] muxed_d;

    mux mux0({d[0], q[1], i, q[0]}, s, muxed_d[0]);
    mux mux1({d[1], q[2], q[0], q[1]}, s, muxed_d[1]);
    mux mux2({d[2], q[3], q[1], q[2]}, s, muxed_d[2]);
    mux mux3({d[3], q[4], q[2], q[3]}, s, muxed_d[3]);
    mux mux4({d[4], q[5], q[3], q[4]}, s, muxed_d[4]);
    mux mux5({d[5], q[6], q[4], q[5]}, s, muxed_d[5]);
    mux mux6({d[6], q[7], q[5], q[6]}, s, muxed_d[6]);
    mux mux7({d[7], i, q[6], q[7]}, s, muxed_d[7]);

    dff dff0(q[0], , c, muxed_d[0]);
    dff dff1(q[1], , c, muxed_d[1]);
    dff dff2(q[2], , c, muxed_d[2]);
    dff dff3(q[3], , c, muxed_d[3]);
    dff dff4(q[4], , c, muxed_d[4]);
    dff dff5(q[5], , c, muxed_d[5]);
    dff dff6(q[6], , c, muxed_d[6]);
    dff dff7(q[7], , c, muxed_d[7]);

endmodule
