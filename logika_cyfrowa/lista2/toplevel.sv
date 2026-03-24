module toplevel(input [3:0] i, output o);
    logic a, b, c, d;
    assign {a, b, c, d} = i;

    assign o = ~a&c&d | a&b&~c |
        ~b&c&d | a&b&~d | 
        b&!c&d | a&~c&d | 
        a&~b&d | a&~b&c |
        a&c&~d | b&c&~d | 
        ~a&b&c | ~a&b&d;
endmodule
