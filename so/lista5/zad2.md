# zad2

---

* `urządzenie znakowe` - udostępnia strumień bajtów bez buforowania, po ktrótym czytamy/piszemy po kolei
* `urządzenie blokowe` - obsługuje dane w stałych blokach z fuforowaniem np dysk hdd/sdd/pendrive

---

### krytyka:
* słaba dokumentacja: wiele wywołań jest opisanych skąpo
* problemy z przenośnością: różne systemy mają inne zestawy kodóœ i zachowań 
* bałągan w interface: wywołań ioctl(2) i fcntl(2) przybywało latami bez spójnego planu
* brak wizji na przyszłość: nie ma planu na to jak to naprawić w przyszłości 

### ioctl(2)
ioctl - funkcja do sterowania urządzeń/pliko-obiektór ktory pozwala wykonywać operacje do zwykłego read()/write()
ioctl(int fd, int op, char *argp);

* arg_1: file descriptor
* arg_2: operation code, poniżej są makra do ustawiania op.  __IO, __IOR, __IOW, PPIOWR. można ustawić dzieęki nimi kierunkek transferu (brak/read/write/readWrite). Parameter Length to rozmiar struktury przekazywanej przez 3 argument. grupę np 'T' dla TTY. command to numer polecenia w tej grupie
* arg_3: wskaźnik na dane

ioccom.h
``` c 

/*
* Ioctl's have the command encoded in the lower word, and the size of
* any in or out parameters in the upper word.  The high 3 bits of the
* upper word are used to encode the in/out status of the parameter.
*
*	 31 29 28                     16 15            8 7             0
*	+---------------------------------------------------------------+
*	| I/O | Parameter Length        | Command Group | Command       |
*	+---------------------------------------------------------------+
*/

#define	IOCPARM_MASK	0x1fff		/* parameter length, at most 13 bits */
#define	IOCPARM_SHIFT	16
#define	IOCGROUP_SHIFT	8
#define	IOCPARM_LEN(x)	(((x) >> IOCPARM_SHIFT) & IOCPARM_MASK)
#define	IOCBASECMD(x)	((x) & ~(IOCPARM_MASK << IOCPARM_SHIFT))
#define	IOCGROUP(x)	(((x) >> IOCGROUP_SHIFT) & 0xff)

#define	IOCPARM_MAX	NBPG	/* max size of ioctl args, mult. of NBPG */
				/* no parameters */
#define	IOC_VOID	(unsigned long)0x20000000
				/* copy parameters out */
#define	IOC_OUT		(unsigned long)0x40000000
				/* copy parameters in */
#define	IOC_IN		(unsigned long)0x80000000
				/* copy parameters in and out */
#define	IOC_INOUT	(IOC_IN|IOC_OUT)
				/* mask for IN/OUT/VOID */
#define	IOC_DIRMASK	(unsigned long)0xe0000000

#define	_IOC(inout, group, num, len) \
    ((inout) | (((len) & IOCPARM_MASK) << IOCPARM_SHIFT) | \
    ((group) << IOCGROUP_SHIFT) | (num))

#define	_IO(g,n)	_IOC(IOC_VOID,	(g), (n), 0)
#define	_IOR(g,n,t)	_IOC(IOC_OUT,	(g), (n), sizeof(t))
#define	_IOW(g,n,t)	_IOC(IOC_IN,	(g), (n), sizeof(t))

/* this should be _IORW, but stdio got there first */
#define	_IOWR(g,n,t)	_IOC(IOC_INOUT,	(g), (n), sizeof(t))

#define IOCSNPRINTF(buf, len, cmd) \
    snprintf((buf), (len), "_IO%s%s('%c', %hhu)", \
	(((cmd) >> 30) & 1) ? "R" : "", \
	(((cmd) >> 30) & 2) ? "W" : "", \
	(char)IOCGROUP(cmd), (unsigned char)(cmd))
```

`DIOCEJECT` - https://nxr.netbsd.org/xref/src/sys/sys/dkio.h
`#define DIOCEJECT	_IOW('d', 112, int)	/* eject removable disk */`
`KIOCTYPE` - https://nxr.netbsd.org/xref/src/sys/dev/sun/kbio.h
`#define	KIOCTYPE	_IOR('k', 9, int)	/* get keyboard type */`

`SIOCGIFCONF` - https://nxr.netbsd.org/xref/src/sys/sys/sockio.h
`#define	SIOCGIFCONF	_IOWR('i', 38, struct ifconf)	/* get ifnet list */`