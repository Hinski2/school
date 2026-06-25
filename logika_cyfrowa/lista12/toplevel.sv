module memory (input logic clk, x, input logic [2:0] read_addr, write_addr,
               input logic [7:0] write_data, output logic [7:0] read_data
);
    logic [7:0] mem [0:7];
    always_ff @(posedge clk) begin 
        read_data <= mem[read_addr];
        if(x) mem[write_addr] <= write_data;
    end
endmodule 


module toplevel(input logic clk, nrst, start, wr, input logic [2:0] addr,
            input logic [7:0] datain, output logic [7:0] dataout, output logic ready 
);
    logic [2:0] i, j, j_m;
    logic [7:0] m, c; 
    logic [2:0] read_addr, write_addr;
    logic [7:0] write_data; 
    logic x;

    memory mem(clk, x, read_addr, write_addr, write_data, c);

    typedef enum logic [2:0] { READY, INNER, OUTER, END, SWAP} state_enum;
    state_enum state;

    always_comb begin 
        if(ready && start) read_addr = 3'd0;
        else if(ready) read_addr = addr;
        else if(state == INNER) read_addr = (j == 3'd7) ? i : j + 3'd1;
        else read_addr = i + 3'd1;
    end

    always_comb begin 
        x = 0;
        write_addr = 0;
        write_data = 0;

        if(ready) begin x = wr; write_addr = addr; write_data = datain; end
        else if(state == END) begin x = 1'b1; write_addr = j_m; write_data = c; end 
        else if(state == SWAP) begin x = 1'b1; write_addr = i; write_data = m; end 
    end

    assign dataout = c; 
    assign ready = (state == READY);

    always_ff @(posedge clk, negedge nrst) 
        if(!nrst) begin state <= READY; i <= 0; j <= 0; j_m <= 0; m <= 0; end 
        else case(state)
            READY: if(start) begin i <= 0; state <= OUTER; end 
            INNER:
                begin 
                    if(c < m) begin m <= c; j_m <= j; end 
                    if(j == 3'd7) state <= END;
                    else j <= j + 3'd1;
                end 
            OUTER:
                if(i == 3'd7) state <= READY;
                else begin j <= i + 3'd1; j_m <= i; m <= c; state <= INNER; end 
            END: state <= SWAP;
            SWAP: begin i <= i + 3'd1; state <= OUTER; end 
        endcase
endmodule

