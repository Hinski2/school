module dec2to4(
    input [1:0] i,
    input en,
    output [3:0] o
);
    integer k;
    always_comb
        for (k = 0; k <= 3; k = k + 1)
            if (i == k) // mamy blok if, ale brakuje bloku else
                o[k] = en;
endmodule
// mamy blok if, ale brakuje bloku else. więc gdzy i != k narzędzie do syntezy domyśli
// się że ma zachować poprzednia wartości i wstawi latche - a to już nie będize układ kombinatoryczny

module dec2to4(
    input [1:0] i,
    input en,
    output [3:0] o
);
    integer k;
    always_comb
        o = 4'b0; // domyślnie wszystko wyłączone
        for (k = 0; k <= 3; k = k + 1)
            if (i == k) // mamy blok if, ale brakuje bloku else
                o[k] = en;
endmodule
