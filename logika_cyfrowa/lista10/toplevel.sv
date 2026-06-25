module toplevel(input nrst, step, push, input signed [15:0] d, input [1:0] op,
                output logic signed [15:0] out, output logic [9:0] cnt);
    logic [15:0] mem [0:1023];
    logic signed [15:0] second;
    assign second = mem[cnt - 10'd2];

    always_ff @(posedge step)
        if(push && cnt < 1023)
            mem[cnt - 10'd1] <= out;

    always_ff @(posedge step, negedge nrst) 
        if(!nrst) begin
            cnt <= 0; 
            out <= 0;
        end else if(push && cnt < 1023) begin
            cnt <= cnt + 1;
            out <= d;  
        end else if(!push) case(op)
            1: if(cnt > 0) out <= -out;
            2: if(cnt > 1) begin out <= out + second; cnt <= cnt - 10'd1; end
            3: if(cnt > 1) begin out <= out * second; cnt <= cnt - 10'd1; end 
        endcase
endmodule
