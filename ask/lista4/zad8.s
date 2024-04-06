.global to_upercase

# przyjmuje argument w rax
# zwracam rax

    # ro niw jest funkcja
    # 0x20 oznacza dużą litere 
    movabs    $0x20202020202020,    %r9
    
    movq    %rax,   %rdi
    and     %r9,    %rdi    # branie tylko bitów oznaczających duża litere
    notq    %rdi

    # usówam bity oznaczające dużą literę tam gdzie to konieczne
    and     %rdi,   %rax    

    # to nie jest funkcja po prostu mamy dane dane w rax
    movabs  $0xDFDFDFDFDFDFDFDF,    %r9
    andq    %r9,    %rax

    # to jednak nie jest funkcja po prostu mamy dane dane w rax
    movl    $0xDFDFDFDF,    %r8
    movl    $0xDFDFDFDF,    %r9
    shlq    $5,  %r8
    orq     %r8,    %r9

    andq    %r9,    %rax


# DF
; mov r9d, 0x20202020         ; Move lower 32 bits into r9, clears upper 32 bits
; mov rax, 0x20202020         ; Move the value into rax as a temporary register
; shl rax, 32                 ; Shift left by 32 bits to prepare for the upper 32 bits
; or r9, rax  
