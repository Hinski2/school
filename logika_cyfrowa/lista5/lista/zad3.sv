/*
    dekoder 2 do 4 z bitem aktywacji:
        w == 0 -> 0001
        w == 1 -> 0010
        w == 2 -> 0100
        w == 3 -> 1000

    czemu jest źle zakodowane:
        * mamy 4 osobne sygnały zamiast wektora
        * if'y sugeruja że mamy jakiś priorytet, a (jak w enkoderze priorytetowym), a my tu rzadnego priorytetu nie mamy,
            wartości w są wzajemnie wykluzcające
        * można ten ukłąd opisaż z uzyciem assigne
*/
module zadanie(
    input [1:0] w,
    input en,
    output logic y0, y1, y2, y3
);
    always_comb begin
        y0 = 0;
        y1 = 0;
        y2 = 0;
        y3 = 0;
        if (en)
            if (w == 0) y0 = 1;
            else if (w == 1) y1 = 1;
            else if (w == 2) y2 = 1;
            else y3 = 1;
    end
endmodule


module zadanie(
    input [1:0] w,
    input en,
    output logic y0, y1, y2, y3
);
    assign y = en ? (4'b1 << w) : 4'b0;
endmodule
