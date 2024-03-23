.global to_upercase

# przyjmuje argument w rdi
# zwracam rdx
to_upercase: 
    # 0x20 oznacza dużą litere 
    movq    $0x$0x2020202020202020,    %r9

    movq    %rdi,   %rdx    # dodawanie kopii rdi do rdx
    and     %r9,    %rdi    # branie tylko bitów oznaczających duża litere
    notq    %rdi

    # usówam bity oznaczające dużą literę tam gdzie to konieczne
    and     %rdi,   %rdx    

    ret
