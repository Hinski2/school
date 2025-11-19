# zad2

---
`Wskazówka: Rozważ uprawnienia katalogu «/usr/local» i «/tmp»`

    drwxr-xr-x 11 root root 4096 Oct 29 23:41 .
    d - typ: katalog
    prawa usera (włąśniciela)
    prawa grupy
    prawa innych 
    11 - liczba dowiaązań do katalogu
    root - właściciel
    root - grupa właściciela
    4096 - rozmiar katalogu w bajtach 
    data ostatniej modyfikacji 
    nazwa


### jaka rolę pełnia bity uprawnień <rwx> dla katolagów 
r(read) - pozwala czytać pliste plikóœ w katalogu
w(write) - pozwala modyfikować zawartośc katalogu
x(execute) pozwala wejść do katalogo (cd)

### opisz znaczie pitów set-git i sticki dla katalogów 
set-gid (s) - nowo tworzone pliki dziedziczą grupę patalogu. now podkatalogi dziecziczą też set-gid
sticky (t) - usuwać lub zmieniać nazwę pliku może tylko właściciel katalogu / root

### napisz w pseudokodzie procedure
dla procesu o tożsamości zadanej przez getuid(2) i getgroups(2) procedura sparawdza zcy proces ma upoważniony dostęp `mode` do pliku o metadanych wczytanych do `sb`

``` c
struct stat {
    dev_t      st_dev;      /* ID of device containing file */
    ino_t      st_ino;      /* Inode number */
    mode_t     st_mode;     /* File type and mode */
    nlink_t    st_nlink;    /* Number of hard links */
    uid_t      st_uid;      /* User ID of owner */
    gid_t      st_gid;      /* Group ID of owner */
    dev_t      st_rdev;     /* Device ID (if special file) */
    off_t      st_size;     /* Total size, in bytes */
    blksize_t  st_blksize;  /* Block size for filesystem I/O */
    blkcnt_t   st_blocks;   /* Number of 512 B blocks allocated */

    /* Since POSIX.1-2008, this structure supports nanosecond
        precision for the following timestamp fields.
        For the details before POSIX.1-2008, see VERSIONS. */

    struct timespec  st_atim;  /* Time of last access */
    struct timespec  st_mtim;  /* Time of last modification */
    struct timespec  st_ctim;  /* Time of last status change */
};
```
`struct stat *sb` - wskaźnik na strukture przechowującą informacje o pliku
`int mode` - 
* F_OK - sprawdza czy plik istnieje
* R_OK - sprawdza czy można czytać i czy plik istnieje 
* W_OK - sprawdza czy można pisac i czy plik istnieje
* X_OK - sprawdza czy można wejść/wykonać i czy plik istnieje

``` c
bool my_access(struct stat *sb, int mode) {
    uid = getuid()
    gids = getgroups()  // lista grup procesu

    // sprawdzanie czy plik istnieje 
    if(sb == NULL and mode & F_OK) // jeśli sb, to plik musi istnieć
        return false

    // sprawdzenie dla root'a 
    if(uid == 0) { // root może r, w, ale jeśli x nie jest zapalony to nawet on tego nie wykona
        if(mode & X_OK and !(sb -> st_mode & 0b001001001)) return false // sprawdzenie czy choć jeden x jest ustawiony
        return true
    }

    // ustalenie która grupa nas interesuje
    if(sb -> set_uid == uid) {
        permisions = sb -> st_mode >> 6;
    } elif (sb -> set_gid in gids) {
        permisions = sb -> st_mode >> 3;
    } else {
        permisions = sb -> st_mode;
    }

    // sprawdzenie R_OK, W_OK, X_OK
    if(mode & R_OK and permisions & 0b100) return false;
    if(mode & W_OK and permisions & 0b010) return false;
    if(mode & X_OK and permisions & 0b001) return false;

    return true;
}

```