/*
    open - 000
    close - 001
    cook - 010
    pause - 011
    bell - 100

*/
module toplevel(input clk, nrst, door, start, finish,
                output logic heat, light, bell);
    logic [2:0] state;

    always_ff @(posedge clk, negedge nrst)
        if(!nrst) state <= 3'b001;
        else case(state)
            3'b000: if(!door) state <= 3'b001;
            3'b001: if(door) state <= 3'b000; else if(start) state <= 3'b010;
            3'b010: if(door) state <= 3'b011; else if(finish) state <= 3'b100;
            3'b011: if(!door) state <= 3'b010;
            3'b100: if(door) state <= 3'b000;
        endcase 


    always_comb begin
        heat = 0;
        light = 0;
        bell = 0;
        case(state)
            3'b000: light = 1;
            3'b010: begin light = 1; heat = 1; end
            3'b011: light = 1;
            3'b100: bell = 1;
        endcase
    end
endmodule
