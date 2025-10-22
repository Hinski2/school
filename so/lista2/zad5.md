# zad5 

---

``` c
      1 
      2 #include <sys/types.h>
      3 #include <sys/wait.h>
      4 
      5 #include <signal.h>
      6 #include <stdio.h>
      7 #include <stdlib.h>
      8 #include <unistd.h>
      9 
     10 #define LEN(x)	(sizeof (x) / sizeof *(x))
     11 #define TIMEO	30
     12 
     13 static void sigpoweroff(void);
     14 static void sigreap(void);
     15 static void sigreboot(void);
     16 static void spawn(char *const []);
     17 
     18 static struct { // struktura mapująca sygnał do jego handlera
     19 	int sig;
     20 	void (*handler)(void);
     21 } sigmap[] = {
     22 	{ SIGUSR1, sigpoweroff },
     23 	{ SIGCHLD, sigreap     },
     24 	{ SIGALRM, sigreap     },
     25 	{ SIGINT,  sigreboot   },
     26 };
     27 
     28 #include "config.h"
     29 
     30 static sigset_t set;
     31 
     32 int
     33 main(void)
     34 {
     35 	int sig;
     36 	size_t i;
     37 
     38 	if (getpid() != 1)  // jeśli nie mamy pid = 1 to kończymy, bo to ma być proces init
     39 		return 1;
     40 	chdir("/");         // zmienia working dir na /
     41 	sigfillset(&set);   // inicjalizuje i wypełnia set sygnałów  
     42 	sigprocmask(SIG_BLOCK, &set, NULL); // sigprocmask to funkcja ktora sprowadza i/lub zmienia maski sygnałów. tutaj SIG_BLOCK blokuje wszystkie sygnały 
     43 	spawn(rcinitcmd);   // uruchamia "/bin/rc.init"
     44 	while (1) {
     45 		alarm(TIMEO);   // ustawia alarm na 30s
     46 		sigwait(&set, &sig);    // wstrzymuje wykonywanie kodu do przyjścia sygnału i zapisuje go w sig
     47 		for (i = 0; i < LEN(sigmap); i++) { // próhujemy zmapować sygnał do handlera
     48 			if (sigmap[i].sig == sig) {
     49 				sigmap[i].handler();
     50 				break;
     51 			}
     52 		}
     53 	}
     54 	/* not reachable */ // mamy nieskończona pentle wiec tutaj program nigdy nei dotrze
     55 	return 0;
     56 }
     57 
     58 static void
     59 sigpoweroff(void)
     60 {
     61 	spawn(rcpoweroffcmd);   // rcpoweroffcmd = "/bin/rc.shutdown", "poweroff"
     62 }
     63 
     64 static void
     65 sigreap(void)
     66 {
     67 	while (waitpid(-1, NULL, WNOHANG) > 0)  // sprząta dowolne dziecko (-1), nie spamiętuje statusu (NULL), nie blokuj (WNOHANG) -> jesli nei ma dziecka, które już sie zakończyło zwróć 0 
     68 		;
     69 	alarm(TIMEO);   // dzieki temu za 30 s znów pogrzebiemy dzieci 
     70 }
     71 
     72 static void
     73 sigreboot(void)
     74 {
     75 	spawn(rcrebootcmd);     // rcrebootcmd = "/bin/rc.shutdown", "reboot"
     76 }
     77 
     78 static void
     79 spawn(char *const argv[])
     80 {
     81 	switch (fork()) {   // torzymy dziecko
     82 	case 0: // jesteśmy w dziecku
     83 		sigprocmask(SIG_UNBLOCK, &set, NULL);   // odblokowujemy wszystkie sygnały dl dziecka
     84 		setsid();   // zostań liderem nowej sesji
     85 		execvp(argv[0], argv);  // uruchamiamy program, jeśli sie uda to nigdy nie wracamy
     86 		perror("execvp");   // jeśli sie nie uda to wypisujemy błąd i zwracamy 1
     87 		_exit(1);
     88 	case -1: // mamy błąd
     89 		perror("fork");
     90 	}
     91 }
```

``` c
      1 static char *const rcinitcmd[]     = { "/bin/rc.init", NULL };
      2 static char *const rcrebootcmd[]   = { "/bin/rc.shutdown", "reboot", NULL };
      3 static char *const rcpoweroffcmd[] = { "/bin/rc.shutdown", "poweroff", NULL };
```

---

### jakie zadania pełni sinit
* jest minimalnym init (pid=1), wiec startuje system i reaguje na sygnały
* najpierw blokujemy wszystkie sygnały, żeby potem na nie czekać w sigwait()
* próbujemy zmapować sygnał do handlera
    * { SIGUSR1, sigpoweroff },
    * { SIGCHLD, sigreap     },
    * { SIGALRM, sigreap     },
    * { SIGINT,  sigreboot   },

###  w jaki sposób grzebie swoje dzieci
``` c
int sigprocmask(int how, const sigset_t *_Nullable restrict set, sigset_t *_Nullable restrict oldset);
```
odpowiedzialny za sprowadzenie i/lub zmiane maski sygnałów

```c
int sigwait(const sigset_t *restrict set, int *restrict sig);
```
wstrzymuje wykonywanie kodu do przyjścia sygnału i zapisuje go w sig
alarm(TIMEO) działa jak bezpieczkik, jest po to żeby nie zostawic żadnych zombie jeśli cos by poszlo nie tak z SIGCHILD
