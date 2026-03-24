module toplevel(input a, b, c, d, x, y, output o);
  logic a_out, b_out, c_out, d_out;
  
  assign a_out = !x && !y && a;
  assign b_out = !x && y && b;
  assign c_out = x && !y && c; 
  assign d_out = x && y && d;
  
  assign o = a_out || b_out || c_out || d_out;
endmodule
