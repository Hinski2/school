# zad 3

--- 

`strace -o pipeline.log -f dash`
`ps -ef | grep sh | wc -l > cnt`

* 31128 - dash
    * read: 5 i 0
    * write: 2
* 31150 - ps -ef
    * read: 5 i 6
    * write: 1
* 31151 - grep sh
    * read: 5 i 0
    * write: 1
* 31152 - wc -l
    * read: 5 i 0
    * write: 1

otwieranie (tworzenie) pliku:
``` bash 
293:31152 openat(AT_FDCWD, "cnt", O_WRONLY|O_CREAT|O_TRUNC, 0666 <unfinished ...>
```

execve: 
``` bash 
1:31128 execve("/usr/bin/dash", ["dash"], 0x7ffc87402d78 /* 54 vars */) = 0
164:31150 execve("/usr/bin/ps", ["ps", "-ef"], 0x563334cc5258 /* 54 vars */ <unfinished ...>
212:31151 execve("/usr/bin/grep", ["grep", "sh"], 0x563334cc5288 /* 54 vars */ <unfinished ...>
326:31152 execve("/usr/bin/wc", ["wc", "-l"], 0x563334cc52d8 /* 54 vars */ <unfinished ...>
```

dup2 - duplikuje deskryptor pliku
dup2:
``` bash 
151:31150 dup2(6, 1 <unfinished ...>
199:31151 dup2(5, 0 <unfinished ...>
204:31151 dup2(7, 1)                        = 1
282:31152 dup2(6, 0 <unfinished ...>
317:31152 dup2(5, 1 <unfinished ...>
```

pipe:
``` bash 
101:31128 pipe2([5, 6], 0)                  = 0
129:31128 <... pipe2 resumed>[6, 7], 0)     = 0
```

jest wołany przez pid 31128 (powłoke dash)

close:
``` bash
31128 close(5)                          = 0
31151 close(6)                          = 0
31151 close(7 <unfinished ...>
31150 close(1 <unfinished ...>
31150 close(2 <unfinished ...>
31152 close(0 <unfinished ...>
31128 close(10)                         = 0
```

clone - realizuje fork:
``` bash
103:31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fa6f579ce50) = 31150
135:31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
196:31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
```

---

razem:
``` bash
1:   31128 execve("/usr/bin/dash", ["dash"], 0x7ffc87402d78 /* 54 vars */) = 0
101: 31128 pipe2([5, 6], 0) = 0
103: 31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD, child_tidptr=0x7fa6f579ce50) = 31150
129: 31128 <... pipe2 resumed>[6, 7], 0) = 0
135: 31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
151: 31150 dup2(6, 1 <unfinished ...>
164: 31150 execve("/usr/bin/ps", ["ps", "-ef"], 0x563334cc5258 /* 54 vars */ <unfinished ...>
196: 31128 clone(child_stack=NULL, flags=CLONE_CHILD_CLEARTID|CLONE_CHILD_SETTID|SIGCHLD <unfinished ...>
199: 31151 dup2(5, 0 <unfinished ...>
204: 31151 dup2(7, 1) = 1
212: 31151 execve("/usr/bin/grep", ["grep", "sh"], 0x563334cc5288 /* 54 vars */ <unfinished ...>
282: 31152 dup2(6, 0 <unfinished ...>
293: 31152 openat(AT_FDCWD, "cnt", O_WRONLY|O_CREAT|O_TRUNC, 0666 <unfinished ...>
317: 31152 dup2(5, 1 <unfinished ...>
326: 31152 execve("/usr/bin/wc", ["wc", "-l"], 0x563334cc52d8 /* 54 vars */ <unfinished ...>
```
