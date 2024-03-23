.global change_endian
.global change_endian2


# inplementaccja z użyciem bswap https://www.felixcloutier.com/x86/bswap
# argument w edi
# zwraca edx
change_endian:
    movl    %edi,   %edx
    bswap   %edx
    ret

# implementacja z użyciem ror i rol
# argument w edi
# zwraca edx
change_endian2:
    # edi: B4 B3 B2 B1
    # obsługa B1
    movw    %di,    %ax     # edx: XX XX XX B1
    rol     $8,     %edx    # edx: XX XX B1 XX
    ror     $8,     %edi    # edi: B1 B4 B3 B2 

    # obsluga B2
    movw    %di,    %ax     # edx: XX XX B1 B2
    rol     $8,     %edx    # edx: XX B1 B2 XX
    ror     $8,     %edi    # edi: B2 B1 B4 B3

    # obsluga B3
    movw    %di,    %ax     # edx: XX B1 B2 B3
    rol     $8,     %edx    # edx: B1 B2 B3 XX
    ror     $8,     %edi    # edi: B3 B2 B1 B4
    
    # obsluga B4
    movw    %di,    %ax     # edx: B1 B2 B2 B4

    # zwrócenie edx
    ret



