#include <stddef.h>
#include <pthread.h>

// __thread oznacza, że każdy wątemk posiada własną kopię tej zmiennej
__thread long myid; // normalnie nie jest współdzielona ale u nas w lini 20 wątek główny przekazuje wskaźnik do swojej kopii myid nowemu wątkowi
static char **strtab; // istnieje tylko jedna instancja która jest współdzielona

void *thread(void *vargp) { // vargp znajduje sie na stosie kadego utorzonego wątku, nie jest współdzielona
    myid = *(long *)vargp;
    static int cnt = 0; // istnieje tylko jedna instancja która jest współdzielona
    printf("[%ld]: %s (cnt=%d)\n", myid, strtab[myid], ++cnt);
    return NULL;
}

int main(int argc, char *argv[]) { // argc, argv nei są współdzielone
    // argv[0] jest wsþłdzilony bo wątki mają do niej dostęp przez strtab

    strtab = argv;
    while(argc > 0) {
        myid = --argc;
        pthread_create(&tid, NULL, thread, (void *)&myid);
    }

}

/*
    źródłem wyścigu jest:
        * myid, wątek gówny modyfikuje swoje myid w petli (linia 19) a wątek potomy odcytuje tę sama kopie przez wskaźnik 
        * cnt, każdy z nowo utworzonych wątków ma do niej dostęp i ją inkrementuje

*/