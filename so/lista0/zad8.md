# zad 8

---

strace wykonuje program dopuki się nie skończy, w tym czasie przechwytuje wszystkie system calle wywołane przez proces oraz sygnały które otrzymuje proces 

``` c
strace ./2_cat
execve("./2_cat", ["./2_cat"], 0x7ffeebf65ac0 /* 67 vars */) = 0
brk(NULL)                               = 0x5576b2335000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 4
fstat(4, {st_mode=S_IFREG|0644, st_size=145927, ...}) = 0
mmap(NULL, 145927, PROT_READ, MAP_PRIVATE, 4, 0) = 0x7f4ad1ae6000
close(4)                                = 0
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 4
read(4, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000x\2\0\0\0\0\0"..., 832) = 832
pread64(4, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 896, 64) = 896
fstat(4, {st_mode=S_IFREG|0755, st_size=2149728, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4ad1ae4000
pread64(4, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 896, 64) = 896
mmap(NULL, 2174000, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 4, 0) = 0x7f4ad1800000
mmap(0x7f4ad1824000, 1515520, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x24000) = 0x7f4ad1824000
mmap(0x7f4ad1996000, 454656, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x196000) = 0x7f4ad1996000
mmap(0x7f4ad1a05000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x204000) = 0x7f4ad1a05000
mmap(0x7f4ad1a0b000, 31792, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7f4ad1a0b000
close(4)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7f4ad1ae1000
arch_prctl(ARCH_SET_FS, 0x7f4ad1ae1740) = 0
set_tid_address(0x7f4ad1ae1a10)         = 10294
set_robust_list(0x7f4ad1ae1a20, 24)     = 0
rseq(0x7f4ad1ae1680, 0x20, 0, 0x53053053) = 0
mprotect(0x7f4ad1a05000, 16384, PROT_READ) = 0
mprotect(0x5576ac21b000, 4096, PROT_READ) = 0
mprotect(0x7f4ad1b4b000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
getrandom("\xe9\xc2\x6e\x1f\x0d\x87\xd6\x8a", 8, GRND_NONBLOCK) = 8
munmap(0x7f4ad1ae6000, 145927)          = 0
read(0XD
, "XD\n", 4096)                   = 3
write(1, "XD\n", 3XD
)                     = 3
read(0, "", 4096)                       = 0
exit_group(0)                           = ?
+++ exited with 0 +++
```

---

`read(0, "XD\n", 4096) = 3`
    program wykonuje read na fd=0 (stdin) i zwraca 3 bajty
`write(1, "XD\n", 3) = 3`
    progam wypisuje te same t bajty na fd=1 (stdout)
`read(0, "", 4096) = 0`
    program zwrócil 0, wciśnięciu CTRL+D, i kończy swoje działanie

---

### czytanie katalogu zamista pliku

``` c
strace ./2_cat include

execve("./2_cat", ["./2_cat", "include"], 0x7ffdf6c98538 /* 67 vars */) = 0
brk(NULL)                               = 0x558115192000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 4
fstat(4, {st_mode=S_IFREG|0644, st_size=145927, ...}) = 0
mmap(NULL, 145927, PROT_READ, MAP_PRIVATE, 4, 0) = 0x7fa832905000
close(4)                                = 0
openat(AT_FDCWD, "/usr/lib/libc.so.6", O_RDONLY|O_CLOEXEC) = 4
read(4, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0000x\2\0\0\0\0\0"..., 832) = 832
pread64(4, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 896, 64) = 896
fstat(4, {st_mode=S_IFREG|0755, st_size=2149728, ...}) = 0
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fa832903000
pread64(4, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 896, 64) = 896
mmap(NULL, 2174000, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 4, 0) = 0x7fa832600000
mmap(0x7fa832624000, 1515520, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x24000) = 0x7fa832624000
mmap(0x7fa832796000, 454656, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x196000) = 0x7fa832796000
mmap(0x7fa832805000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 4, 0x204000) = 0x7fa832805000
mmap(0x7fa83280b000, 31792, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x7fa83280b000
close(4)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7fa832900000
arch_prctl(ARCH_SET_FS, 0x7fa832900740) = 0
set_tid_address(0x7fa832900a10)         = 13261
set_robust_list(0x7fa832900a20, 24)     = 0
rseq(0x7fa832900680, 0x20, 0, 0x53053053) = 0
mprotect(0x7fa832805000, 16384, PROT_READ) = 0
mprotect(0x5580e6e6a000, 4096, PROT_READ) = 0
mprotect(0x7fa83296a000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
getrandom("\x80\xda\x46\x10\x95\x87\x0c\x49", 8, GRND_NONBLOCK) = 8
munmap(0x7fa832905000, 145927)          = 0
openat(AT_FDCWD, "include", O_RDONLY)   = 4
read(4, 0x7ffc8435a9b0, 4096)           = -1 EISDIR (Is a directory)
brk(NULL)                               = 0x558115192000
brk(0x5581151b3000)                     = 0x5581151b3000
write(2, "read error: Is a directory\n", 27read error: Is a directory
) = 27
exit_group(1)                           = ?
+++ exited with 1 +++
```

dostaniemy `read error: Is a directory` na stderr