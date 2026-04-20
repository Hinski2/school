module try_swap(input [3:0] a, input [3:0] b, output [3:0] le, output [3:0] gt);
    assign le = (a <= b) ? a : b;
    assign gt = (a <= b) ? b : a;
endmodule

// idea rozwiąaznia taka jak rysunek na wikipedii z linka z polecenia
module toplevel(input [15:0] i, output [15:0] o);
   wire [3:0] a0, c0;
   try_swap tsa_c(i[3:0], i[11:8], a0, c0);

   wire [3:0] b0, d0;
   try_swap tsb_d(i[7:4], i[15:12], b0, d0);

   wire [3:0] a1, b1;
   try_swap tsa_b(a0, b0, a1, b1);

   wire [3:0] c1, d1;
   try_swap tsc_d(c0, d0, c1, d1);

   wire [3:0] b2, c2;
   try_swap tsb_c(b1, c1, b2, c2);

   assign o = {d1, c2, b2, a1};
endmodule

