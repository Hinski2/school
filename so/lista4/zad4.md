# zad 4

---


* 31128 - dash
* 31150 - ps -ef
* 31151 - grep sh
* 31152 - wc -l

`setpgid(pid, pgid)`

``` bash
78:31128 setpgid(0, 31128)                 = 0  # dash ustawia swoja pgid na pid i staje się liderem
105:31128 setpgid(31150, 31150)             = 0 # dash ustawia pgid ps na pid ps czyli tworzy nową grupe procesów dal całego potoku
122:31150 setpgid(0, 31150 <unfinished ...> # ps ustawia swój pgid na pgid potoku
148:31128 setpgid(31151, 31150 <unfinished ...> # dash dołącza grepa do grupy potoku 
161:31151 setpgid(0, 31150 <unfinished ...> # grep ustawia swój pgid na pgid potoku
214:31128 setpgid(31152, 31150)             = 0 # dash dołącza wc do grupy potoku
239:31152 setpgid(0, 31150 <unfinished ...> # wc ustawia swój pgid na pgid potoku
4821:31128 setpgid(0, 31126)                 = 0 # dash przestawia swój pid na inny
```
pgid ustawia sie 2 razy by uniknąć race condition

grupa pierdszoplanowa jest ustawiana przez `ioctl(TIOCSPGRP)`

``` bash 
58:31128 ioctl(0, TCGETS2, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|B38400<<IBSHIFT|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
59:31128 ioctl(1, TCGETS2, {c_iflag=ICRNL|IXON|IUTF8, c_oflag=NL0|CR0|TAB0|BS0|VT0|FF0|OPOST|ONLCR, c_cflag=B38400|B38400<<IBSHIFT|CS8|CREAD, c_lflag=ISIG|ICANON|ECHO|ECHOE|ECHOK|IEXTEN|ECHOCTL|ECHOKE, ...}) = 0
70:31128 ioctl(10, TIOCGPGRP, [31126])     = 0 # ustawienie na fg 31126
80:31128 ioctl(10, TIOCSPGRP, [31128])     = 0 # ustawienie na fg 31128
130:31150 ioctl(10, TIOCSPGRP, [31150] <unfinished ...> # ustawienie na fg 3115o
170:31151 ioctl(10, TIOCSPGRP, [31150] <unfinished ...>
249:31152 ioctl(10, TIOCSPGRP, [31150] <unfinished ...>
712:31150 ioctl(1, TIOCGWINSZ, 0x7ffc2b795da0) = -1 ENOTTY (Inappropriate ioctl for device)
713:31150 ioctl(2, TIOCGWINSZ, {ws_row=60, ws_col=152, ws_xpixel=2128, ws_ypixel=1860}) = 0
714:31150 ioctl(1, TCGETS2, 0x7ffc2b795d40) = -1 ENOTTY (Inappropriate ioctl for device)
4789:31128 ioctl(10, TIOCSPGRP, [31128])     = 0 # ustawienie na fg 31128
4819:31128 ioctl(10, TIOCSPGRP, [31126])     = 0 # ustawienie na fg 31126
```

fd 10 to terminal sterujący 

31126 jest rodzicem powłoki czyli to nasz strace

kod wyjścia z potoku jest wyznaczany przez: kod wyjścia z całego potoku to kod ostatniej komendy w pokotku 