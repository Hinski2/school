module toplevel(input logic clk, nrst, start,
                input logic [7:0] ina, inb,
                output logic ready, output logic [7:0] out);
    logic [7:0] a, b;
    assign out = a;

    always_ff @(posedge clk, negedge nrst) 
        if(!nrst) ready <= 1;
        else if(ready) begin 
            if(start) begin
                a <= ina;
                b <= inb;
                ready <= 0;
            end
        end else if(a == b) ready <= 1;
        else if(a < b) begin a <= b; b <= a; end 
        else a <= a - b;

endmodule
