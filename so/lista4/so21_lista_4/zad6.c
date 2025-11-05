#include "caplib/csapp.h"

bool f_lock(const char *path) {
    if(access(path, F_OK) == 0) 
        return false 

    // wczedzy sprawdzaniem a użyciem ktoś może namieszać 
    (void) Open(path, O_CREAT|O_WRONLY, 0700)
    return true;
}

/*
0700 - rwx tylko dla właściciela (prawa nowo tworzonego pliku)
o_creat - stwórz plik jeśli nie istnieje
o_wronly - otwórz w trybie writing only
o_excl - fail jeśli plik istnieje
o_cloexec - automatycznie zamyka plik na execve

If O_CREAT is set, but file already exists, this	flag has no effect ex-
       cept when O_EXCL	is set too, in this case  open()  fails	 with  EEXIST.
*/

bool f_lock_fixed(int dirFd, const char *name) {
    int fd = openat(dirFd, name, O_CREAT|O_WRONLY|O_EXCL|O_CLOEXEC, 0700); // jeśli nam się uda to jest blokada
    if(fd >= 0) {
        close(fd);
        return true;
    }

    return false;
}

void f_unlock(const char *path) {
    Unlink(path);
}