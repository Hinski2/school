module toplevel(input logic clk, nrst, start,
                input logic [15:0] inx, input logic [7:0] inn,
                output logic ready, output logic [15:0] out);
    logic [15:0] a, x;
    logic [7:0] n;

    always_ff @(posedge clk, negedge nrst) begin 
        if(!nrst) ready <= 1;
        else if(ready) begin
            if(start) begin
                a <= 16'd1;
                x <= inx;
                n <= inn;
                ready <= 0;
            end 
        end else begin
            if(n == 0) begin out <= a; ready <= 1; end
            else if((n & 1'b1) == 0) begin x <= x * x; n <= n >> 1; end
            else begin a <= a * x; n <= n - 1; end
        end
    end
endmodule
