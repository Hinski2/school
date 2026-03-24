// półsumator i sumator taki sam jak z wykładu 1
module polsumator(output s, cout, input a, b);
    xor (s, a, b);
    and (cout, a, b);
endmodule

module sumator(output s, cout, input a, b, cin);
    logic ps1s, ps1c, ps2c;
    polsumator ps1(ps1s, ps1c, a, b);
    polsumator ps2(s, ps2c, ps1s, cin);
    or (cout, ps1c, ps2c);
endmodule

// funkcje do dodawania
module add_bit(input [3:0] a, input [3:0] b, input cin, output [3:0] s, output cout);
    logic c1, c2, c3;

    sumator s0(s[0], c1, a[0], b[0], cin);
    sumator s1(s[1], c2, a[1], b[1], c1);
    sumator s2(s[2], c3, a[2], b[2], c2);
    sumator s3(s[3], cout, a[3], b[3], c3);

endmodule

module bcd_add(input [3:0] a, input [3:0] b, input cin, output [3:0] s, output cout);
    logic [3:0] raw_s;
    logic raw_cout;

    add_bit add1(a, b, cin, raw_s, raw_cout);
    assign cout = raw_cout | (raw_s[3] & raw_s[2]) | (raw_s[3] & raw_s[1]);
    
    logic [3:0] fix_bit;
    logic fix_c, raw_cout2;
    assign fix_bit = {1'b0, cout, cout, 1'b0};
    assign fix_c = 1'b0;
    add_bit add2(raw_s, fix_bit, fix_c, s, raw_cout2);

endmodule

module complement_to_9(input [3:0] i, output [3:0] o);
    assign o[0] = ~i[0];
    assign o[1] = i[1];
    assign o[2] = (i[1] ^ i[2]) & ~i[3];
    assign o[3] = ~i[1] & ~i[2] & ~i[3];

endmodule

module toplevel(input [7:0] a, input [7:0] b, input sub, output [7:0] o);
    logic [3:0] b_low_compl, b_hi_compl;
    complement_to_9 compl_lo(b[3:0], b_low_compl);
    complement_to_9 compl_hi(b[7:4], b_hi_compl);
    
    logic [3:0] b_low, b_hi;
  	assign b_low = (b[3:0] & {4{~sub}}) | (b_low_compl & {4{sub}});
    assign b_hi  = (b[7:4] & {4{~sub}}) | (b_hi_compl & {4{sub}});

    logic c, c2;
    bcd_add add_lo(a[3:0], b_low, sub, o[3:0], c);
  	bcd_add add_hi(a[7:4], b_hi, c, o[7:4], c2);
    
endmodule

