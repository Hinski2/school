# zad1

### zad mat pomocjiczy czarny król, biała wierza, bialy król

preprocesing
znalezienie wszystkich pozycji matujących

heurystyka:
majmniejsza suma odległości figur od pozycji matującej dla danego ustawienia

### zad normalny mat czarny królm czarna wierza, biała wierza, biały król

heurystyka:
    odl(bk, ck) + odl(bw,cw) + odl(bw, ck)+ odl_do_bezpiecznej_wirzy + ilość_możliwych_ruchów_czarnego_króla
