module toplevel(input [31:0] i, output logic [31:0] o);
    integer k;
    assign o[31] = i[31];

    always_comb begin 
        for(k = 30; k >= 0; k = k - 1) 
            o[k] = i[k] ^ o[k + 1];
    end
endmodule
