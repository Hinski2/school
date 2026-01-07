# zad 5 

--- 

### Jeden z wątków zawoła   `fork(2)`, `execve(2)`,  `exit_group(2)`

fork: kopiowany jest tylką wątek który wywołał forka 
execve: przeżywa tylko wątke który wywołał execve, reszta ginie
exit_group: wszytkie wątki giną 

### Który wątek będzie obsługiwał  `SIGINT` 
Sygnał zostanie obsłużony w kontekście jednego losowo wybranego wątku spośród tych które nie maja zablokowanego tego sygnału. POSIX nie gwarantuje który wątek dostanie sygnał 

### Jeden wątek probuje pisać do rury której drugi koniec jest zamknięty
cały proces zostanie zabity (czyli też wszystkie wątki)

### Czytanie wieloma wątkami tego samego pliku
read(2):

    BUGS         top

       According to POSIX.1-2008/SUSv4 Section XSI 2.9.7 ("Thread
       Interactions with Regular File Operations"):

           All of the following functions shall be atomic with respect to
           each other in the effects specified in POSIX.1-2008 when they
           operate on regular files or symbolic links: ...

       Among the APIs subsequently listed are read() and readv(2).  And
       among the effects that should be atomic across threads (and
       processes) are updates of the file offset.  However, before Linux
       3.14, this was not the case: if two processes that share an open
       file description (see open(2)) perform a read() (or readv(2)) at
       the same time, then the I/O operations were not atomic with
       respect to updating the file offset, with the result that the
       reads in the two processes might (incorrectly) overlap in the
       blocks of data that they obtained.  This problem was fixed in
       Linux 3.14.

* read jest atomowy
* wątki dzielą tablice deskryptorów plików
więc jedyny problem może byc taki że wątek przeczyta coś czego nie chciał przeczytać (bo np inny wątek przesunoł kursor)