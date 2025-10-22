# zad4 

---

* `sygnały oczekujące` - 

---

### użycie kill, pkill, xkill. który jest wysyłany domyślnie
* kill: `ps aux | grep xeyes`, `kill [pid]`
    * domyślnie 15 `SIGTERM`(grzeczne zakończenie), jeśli damy kill -9 to `SIGKILL`
* pkill: `pkill xeyes`
    * domyślnie 15, można zrobić pkill -9
* xkill: `xkill`
    * używa domyślnie `SIGKILL`

### użycie CTRL-Z
* `ctrl+z`
* `jobs`
* `fg` | `fg %1`

### przegląd /proc/[pid]/status

```
Name:	xeyes
Umask:	0022
State:	S (sleeping)
Tgid:	21893
Ngid:	0
Pid:	21893
PPid:	17999
TracerPid:	0
Uid:	1000	1000	1000	1000
Gid:	1000	1000	1000	1000
FDSize:	256
Groups:	985 986 994 998 1000 
NStgid:	21893
NSpid:	21893
NSpgid:	21893
NSsid:	17999
Kthread:	0
VmPeak:	  12236 kB
VmSize:	  12092 kB
VmLck:	      0 kB
VmPin:	      0 kB
VmHWM:	   8776 kB
VmRSS:	   8776 kB
RssAnon:	    524 kB
RssFile:	   8252 kB
RssShmem:	      0 kB
VmData:	    476 kB
VmStk:	    132 kB
VmExe:	     12 kB
VmLib:	   3500 kB
VmPTE:	     52 kB
VmSwap:	      0 kB
HugetlbPages:	      0 kB
CoreDumping:	0
THP_enabled:	1
untag_mask:	0xffffffffffffffff
Threads:	1
SigQ:	0/126380
SigPnd:	0000000000000000
ShdPnd:	0000000000000000
SigBlk:	0000000000000000
SigIgn:	0000000000000000
SigCgt:	0000000000000000
CapInh:	0000000800000000
CapPrm:	0000000000000000
CapEff:	0000000000000000
CapBnd:	000001ffffffffff
CapAmb:	0000000000000000
NoNewPrivs:	0
Seccomp:	0
Seccomp_filters:	0
Speculation_Store_Bypass:	thread vulnerable
SpeculationIndirectBranch:	conditional enabled
Cpus_allowed:	ffff
Cpus_allowed_list:	0-15
Mems_allowed:	00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000000,00000001
Mems_allowed_list:	0
voluntary_ctxt_switches:	48
nonvoluntary_ctxt_switches:	0
x86_Thread_features:	
x86_Thread_features_locked:	
```

* SigQ - liczba sygnałów obecnie zakolekowanych
* SigPnd - sygnały oczekujące (pending)
* SigBlk - sygnały zblokowane
* SigIgn - sygnaly ignorowane
* SigCgt - sygnały z zainstalowanymi handlerami

### wysyłanie sygnałów

najpierw kill -STOP [pid], potem
* kill -USR1 [pid] 
* kill -USR2 [pid]
* kill -HUP [pid]
* kill -INT [pid]
potem kill -CONT [pid]

zazwyczaj sygnały są dostarczane rosnąco po idx, ale nie możemy tego zakladać 

sighup - 1 (signal hand up, czyli rozłączenie z terminalem)
sigint - 2
sigusr1 - 10
sigusr2 - 12