# zad7

---
ltrace - narzędzie do przechywytywania i wyświetalania wywołań wyonanych przez aplikacje do jej bibliotek współdzielonych 



``` c
ltrace -S ./1_ls .

SYS_brk(0)                                                                                                                                                                                      = 0x55bed3cc8000
SYS_access("/etc/ld.so.preload", 04)                                                                                                                                                            = -2
SYS_openat(0xffffff9c, 0x7fac35da81aa, 0x80000, 0)                                                                                                                                              = 4
SYS_fstat(4, 0x7ffecf0e4a50)                                                                                                                                                                    = 0
SYS_mmap(0, 0x250a3, 1, 2)                                                                                                                                                                      = 0x7fac35d4d000
SYS_close(4)                                                                                                                                                                                    = 0
SYS_openat(0xffffff9c, 0x7fac35db7fd0, 0x80000, 0)                                                                                                                                              = 4
SYS_read(4, "\177ELF\002\001\001\003", 832)                                                                                                                                                     = 832
SYS_pread(4, 0x7ffecf0e4730, 896, 64)                                                                                                                                                           = 896
SYS_fstat(4, 0x7ffecf0e4a40)                                                                                                                                                                    = 0
SYS_mmap(0, 8192, 3, 34)                                                                                                                                                                        = 0x7fac35d4b000
SYS_pread(4, 0x7ffecf0e4610, 896, 64)                                                                                                                                                           = 896
SYS_mmap(0, 0x212c30, 1, 2050)                                                                                                                                                                  = 0x7fac35a00000
SYS_mmap(0x7fac35a24000, 0x172000, 5, 2066)                                                                                                                                                     = 0x7fac35a24000
SYS_mmap(0x7fac35b96000, 0x6f000, 1, 2066)                                                                                                                                                      = 0x7fac35b96000
SYS_mmap(0x7fac35c05000, 0x6000, 3, 2066)                                                                                                                                                       = 0x7fac35c05000
SYS_mmap(0x7fac35c0b000, 0x7c30, 3, 50)                                                                                                                                                         = 0x7fac35c0b000
SYS_close(4)                                                                                                                                                                                    = 0
SYS_mmap(0, 0x3000, 3, 34)                                                                                                                                                                      = 0x7fac35d48000
SYS_arch_prctl(4098, 0x7fac35d48740, 0x7fac35d491e0, 34)                                                                                                                                        = 0
SYS_set_tid_address(0x7fac35d48a10, 0x7fac35db6810, 0x7fac35d48740, 34)                                                                                                                         = 0x4e09
SYS_set_robust_list(0x7fac35d48a20, 24, 0x7fac35d48740, 34)                                                                                                                                     = 0
SYS_334(0x7fac35d48680, 32, 0, 0x53053053)                                                                                                                                                      = 0
SYS_mprotect(0x7fac35c05000, 16384, 1)                                                                                                                                                          = 0
SYS_mprotect(0x55bea9bc7000, 4096, 1)                                                                                                                                                           = 0
SYS_mprotect(0x7fac35db4000, 8192, 1)                                                                                                                                                           = 0
SYS_prlimit64(0, 3, 0, 0x7ffecf0e55b0)                                                                                                                                                          = 0
SYS_318(0x7fac35c10200, 8, 1, 0x7ffecf0e55b0)                                                                                                                                                   = 8
SYS_munmap(0x7fac35d4d000, 151715)                                                                                                                                                              = 0
opendir("." <unfinished ...>
SYS_openat(0xffffff9c, 0x7ffecf0e6d61, 0x90800, 0)                                                                                                                                              = 4
SYS_fstat(4, 0x7ffecf0e57a0)                                                                                                                                                                    = 0
SYS_brk(0)                                                                                                                                                                                      = 0x55bed3cc8000
SYS_brk(0x55bed3cf1000)                                                                                                                                                                         = 0x55bed3cf1000
<... opendir resumed> )                                                                                                                                                                         = 0x55bed3cc8010
readdir(0x55bed3cc8010 <unfinished ...>
SYS_getdents64(4, 0x55bed3cc8040, 0x8000, 0)                                                                                                                                                    = 576
<... readdir resumed> )                                                                                                                                                                         = 0x55bed3cc8040
puts(".." <unfinished ...>
SYS_fstat(1, 0x7ffecf0e56c0)                                                                                                                                                                    = 0
SYS_write(1, "..\n", 3..
)                                                                                                                                                                         = 3
<... puts resumed> )                                                                                                                                                                            = 3
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8058
puts("include" <unfinished ...>
SYS_write(1, "include\n", 8include
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8078
puts("." <unfinished ...>
SYS_write(1, ".\n", 2.
)                                                                                                                                                                          = 2
<... puts resumed> )                                                                                                                                                                            = 2
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8090
puts("zad3.md" <unfinished ...>
SYS_write(1, "zad3.md\n", 8zad3.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc80b0
puts("zad2.md" <unfinished ...>
SYS_write(1, "zad2.md\n", 8zad2.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc80d0
puts("2_cat.c" <unfinished ...>
SYS_write(1, "2_cat.c\n", 82_cat.c
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc80f0
puts("2_cat" <unfinished ...>
SYS_write(1, "2_cat\n", 62_cat
)                                                                                                                                                                      = 6
<... puts resumed> )                                                                                                                                                                            = 6
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8110
puts("zad1.md" <unfinished ...>
SYS_write(1, "zad1.md\n", 8zad1.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8130
puts("zad7.md" <unfinished ...>
SYS_write(1, "zad7.md\n", 8zad7.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8150
puts("1_ls" <unfinished ...>
SYS_write(1, "1_ls\n", 51_ls
)                                                                                                                                                                       = 5
<... puts resumed> )                                                                                                                                                                            = 5
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8168
puts("page_table_entry.png" <unfinished ...>
SYS_write(1, "page_table_entry.png\n", 21page_table_entry.png
)                                                                                                                                                      = 21
<... puts resumed> )                                                                                                                                                                            = 21
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8190
puts("libapue" <unfinished ...>
SYS_write(1, "libapue\n", 8libapue
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc81b0
puts("so25_lista_0.pdf" <unfinished ...>
SYS_write(1, "so25_lista_0.pdf\n", 17so25_lista_0.pdf
)                                                                                                                                                          = 17
<... puts resumed> )                                                                                                                                                                            = 17
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc81d8
puts("procesor_package.png" <unfinished ...>
SYS_write(1, "procesor_package.png\n", 21procesor_package.png
)                                                                                                                                                      = 21
<... puts resumed> )                                                                                                                                                                            = 21
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8200
puts("zad6.md" <unfinished ...>
SYS_write(1, "zad6.md\n", 8zad6.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8220
puts("1_ls.c" <unfinished ...>
SYS_write(1, "1_ls.c\n", 71_ls.c
)                                                                                                                                                                     = 7
<... puts resumed> )                                                                                                                                                                            = 7
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8240
puts("Makefile" <unfinished ...>
SYS_write(1, "Makefile\n", 9Makefile
)                                                                                                                                                                   = 9
<... puts resumed> )                                                                                                                                                                            = 9
readdir(0x55bed3cc8010)                                                                                                                                                                         = 0x55bed3cc8260
puts("zad5.md" <unfinished ...>
SYS_write(1, "zad5.md\n", 8zad5.md
)                                                                                                                                                                    = 8
<... puts resumed> )                                                                                                                                                                            = 8
readdir(0x55bed3cc8010 <unfinished ...>
SYS_getdents64(4, 0x55bed3cc8040, 0x8000, 0)                                                                                                                                                    = 0
<... readdir resumed> )                                                                                                                                                                         = 0
closedir(0x55bed3cc8010 <unfinished ...>
SYS_close(4)                                                                                                                                                                                    = 0
<... closedir resumed> )                                                                                                                                                                        = 0
exit(0 <unfinished ...>
SYS_exit_group(0 <no return ...>
+++ exited (status 0) +++
```

---

### \<\<opendir>>
opendir używa: SYS_openat(), SYS_fstat(), SYS_brk()
`SYS_openat(0xffffff9c, 0x7ffecf0e6d61, 0x90800, 0)                                                                                                                                              = 4`

### \<\<readdir>>
reddir używa: SYS_getDents64()
`readdir(0x55bed3cc8010 <unfinished ...>
SYS_getdents64(4, 0x55bed3cc8040, 0x8000, 0))                                                                                                                                                    = 576`


### \<\<printf>>
printf/ pusts to write na fd = 1 czyli stdout
printf używa: SYS_fstat(1, ...)
`SYS_fstat(1, 0x7ffecf0e56c0)                                                                                                                                                                    = 0`


### \<\<closedir>>
closedir używa: SYS_close
`closedir(0x55bed3cc8010 <unfinished ...>
SYS_close(4)`

---

### do czego służy \<\<brk>>
brk ustawia program break, czyli koniec segmentu danych procesu - więc służy od do zmniejszania lub powiększania stery. używa sie go w malloc / free do zarzązania pamięcią 

---
gdb ./1_ls
start .
catch syscall brk
continue
bt

```
(gdb) bt
#0  __brk (addr=addr@entry=0x0) at ../sysdeps/unix/sysv/linux/brk_call.h:24
#1  0x00007ffff7d180fb in __GI___sbrk (increment=increment@entry=167936) at sbrk.c:59
#2  0x00007ffff7ca46c6 in __glibc_morecore (increment=increment@entry=167936) at /usr/src/debug/glibc/glibc/malloc/morecore.c:29
#3  0x00007ffff7ca5621 in sysmalloc (nb=nb@entry=32832, av=0x7ffff7e09ac0 <main_arena>) at malloc.c:2720
#4  0x00007ffff7ca6933 in _int_malloc (av=av@entry=0x7ffff7e09ac0 <main_arena>, bytes=bytes@entry=32816) at malloc.c:4617
#5  0x00007ffff7ca6b1f in __libc_malloc2 (bytes=32816) at malloc.c:3450
#6  0x00007ffff7ce46f6 in __alloc_dir (fd=fd@entry=4, close_fd=close_fd@entry=true, flags=flags@entry=0, statp=statp@entry=0x7fffffffd700) at ../sysdeps/unix/sysv/linux/opendir.c:115
#7  0x00007ffff7ce4780 in opendir_tail (fd=4) at ../sysdeps/unix/sysv/linux/opendir.c:63
#8  0x00007ffff7ce4821 in __opendir (name=<optimized out>) at ../sysdeps/unix/sysv/linux/opendir.c:86
#9  0x0000555555555231 in main (argc=<optimized out>, argv=0x7fffffffd8f8) at 1_ls.c:11
```