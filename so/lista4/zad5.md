# zad 5

---

* `rekord katalogu` - wpis w katalogu mapujący nazwa pliku -> inode
* `metadane` - dodatkowe informacje o pliku
* `dowiązania` - (hard link) wpisy katalogowe wskazujące na inode. przez nie licznik linków rośnie
* `inode` - rekord w systemie plików identyfikowany numerem i przechowujacy metadane pliku i wskaźniki na dane 

---

### czemu nie można czytac i modyfikować katalaogów z użyciem read i write

katalog to specjalna struktura która mapuje nazwy -> i-node, ktora różni się między systemami plików 

jest to po to by użytkownik nie mógł zepsuć struktyry takalogów. nie doszło do niespójnych licznikóœ dowiązań. chcemy by nazwy plików które są w katalogu sie zgadzały i nie były nodeyfikowane przez write

jądro gwarantuje atomowość i spójność przez te syscale

### jakim syscalem można czytać rekord katalogu

ten syscall to `getdents`, w c używamy readdir który korzysta pod spodem z getdents
```c
    struct dirent *entry;
    while((ent = readdir(dir)) != Null) {
        printf("%s", ent -> d_name);
    }
```

### dlaczego zawartośc klatalogu nie jest posortowana

kiddyś do przechowywnia struktury katalogu używało się list, dziś często b-drzewa i hashy. 

więc kolejnosc bywa wegług hasha

posiadanie psortowanych danych wyamagało by większego nakładu pracy na zachowanie kolejnosci niż po prostu lista czy hashe 

zawsze można posortować sobie otrzymane dane

### metaadane katalogu /

``` bash
stat /


    File: /
    Size: 4096      	Blocks: 8          IO Block: 4096   directory
    Device: 259,2	Inode: 2           Links: 17
    Access: (0755/drwxr-xr-x)  Uid: (    0/    root)   Gid: (    0/    root)
    Access: 2025-11-04 23:04:34.484981505 +0100
    Modify: 2025-10-30 18:03:22.251880300 +0100
    Change: 2025-10-30 18:03:22.251880300 +0100
    Birth: 2025-03-19 20:47:56.000000000 +0100
```

* size - rozmiar danch na dysku
* blocks - liczba 512 bajtowych bloków na dysku
* inode - numer inode
* links - liczba hard links
* access prawa dostępu
*access - ostatni odczyt

### czemu jest tyle dowiązań 

``` bash
(base) ➜  / ls -al 
total 60
drwxr-xr-x  17 root root  4096 Oct 30 18:03 .
drwxr-xr-x  17 root root  4096 Oct 30 18:03 ..
lrwxrwxrwx   1 root root     7 Oct 12 18:21 bin -> usr/bin
drwxr-xr-x   5 root root  4096 Nov  4 16:50 boot
drwxr-xr-x  21 root root  4400 Nov  4 21:08 dev
drwxr-xr-x  75 root root  4096 Nov  4 16:50 etc
drwxr-xr-x   3 root root  4096 Mar 19  2025 home
lrwxrwxrwx   1 root root     7 Oct 12 18:21 lib -> usr/lib
lrwxrwxrwx   1 root root     7 Oct 12 18:21 lib64 -> usr/lib
drwx------   2 root root 16384 Mar 19  2025 lost+found
drwxr-xr-x   4 root root  4096 Nov  4 11:35 mnt
drwxr-xr-x   6 root root  4096 Oct  8 20:43 opt
dr-xr-xr-x 378 root root     0 Nov  4 14:08 proc
drwxr-x---   8 root root  4096 Apr  4  2025 root
drwxr-xr-x  25 root root   600 Nov  4 14:08 run
lrwxrwxrwx   1 root root     7 Oct 12 18:21 sbin -> usr/bin
drwxr-xr-x   4 root root  4096 Mar 19  2025 srv
dr-xr-xr-x  13 root root     0 Nov  4 14:08 sys
drwxrwxrwt  30 root root   660 Nov  4 23:53 tmp
drwxr-xr-x  10 root root  4096 Nov  4 16:50 usr
drwxr-xr-x  12 root root  4096 Oct 31 16:52 var
```

15 ( bez bin lin lib64 sbin) + . + .. = 17