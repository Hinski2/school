# zad 3

---

* `argumenty programu` - main(int argc, char *argv[]),  dane które użytkownik przekazuje programowi przy jego uruchomieniu, argv[0] to nazwa programu
* `zmienne środowiskowe` - wartości przechowywane w środowisku procesu które system udostępnia każdemu programowi przy starcie ( to trochę takie zmienne globalne które ustawia os dla wszystkich procesów ), przykłady: 
    * PATH = gdzie system szuka programów np. /usr/bin:/bin
    * Home = katalog domowy uzytkownika
    * USER = nazwa użytkownika
    * PWD = bieżący katalog
można je zobaczyć uzywając `printenv`

--- 

### do czego służy system plików proc(5)
/proc (proc filesystem) to wirtulany system plików, który pokazuje informacje o procesach. jest on wirtulany, bo nie znajduje sie nigdzie na dysku, a jest tworzony "w locie", gdy sie go czyta

dzieki niemu użytkownicy i programy mogą czytać informacje o procesie

### dla wybranego procesu o pid wydrukuj zawartosć katalogu /proc/pid

``` 
sudo ls /proc/1

arch_status	   environ	      maps	     pagemap	   stat
attr		   exe		      mem	     personality   statm
autogroup	   fd		      mountinfo      projid_map    status
auxv		   fdinfo	      mounts	     root	   syscall
cgroup		   gid_map	      mountstats     sched	   task
clear_refs	   io		      net	     schedstat     timens_offsets
cmdline		   ksm_merging_pages  ns	     sessionid     timers
comm		   ksm_stat	      numa_maps      setgroups     timerslack_ns
coredump_filter     limits	      oom_adj	     smaps	   uid_map
cpu_resctrl_groups  loginuid	      oom_score      smaps_rollup  wchan
cwd		   map_files	      oom_score_adj  stack
```

### wyświtl plik zawierajacy argumenty programu i zimnne środowiskowe
argumenty programu znajdują sie w /proc/[pid]/cmdline

``` bash
cat cmdline 
/sbin/initsplash%      
```

zmienne środowiskowe znajduja sie w /proc/[pid]/environ
``` bash 
cat environ
TERM=linux
```

tutaj zmienne srodowiskowe są tki małe bo proces nie został uruchomiony przez powłoke np bash lub zsh, więc nie odziedziczyl srodowiska po innym procesie, jądro ustawilo mi tylko minimalne środowisko potrzebne do dzialania

### podaj znaczenie pół pliku status:

* `uid`: id użytkownika który wywołał proces
* `gid`: id głównej grupy procesu
* `groups`: lista grup do ktorych należy proces 
* `VmPeak`: maksymalne zużycie pamięci wirtualnej procesu w kB
* `VmSize`: aktualna ilość pamięci wirtualnej przypiasnej procesowi
* `VmRSS`: czyli faktyczna ilość pamięci RAM która zajmuje proces w danum momencie
* `Threads`: liczba wątków w procesie (min 1)
* `voluntary_ctx_switches`: liczba dobrowolnych przełączeń kontekstu 
* `nonvoluntary_ctx_switches`: liczba niedobrowolnych przełączeń konteksu


uid: Real Effective Saved Filesystem
* użytkownik który uruchomił proces
* aktualny użytkownik, którego uprawnienia ma proces 
* uid zapamiętany przy zmianie uprawnień 
* uid używany do operacji na plikach