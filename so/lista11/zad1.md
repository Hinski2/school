# zad 1

--- 

* `punkty montażowe` - katalog w głownym drzewie katalogów, ktory służy jako punkt dostępu do podłączonego systemu plików znajdującego się na innym urządzeniu lub partycji
* `pseudo system plików` - wirtualny system plików istniejacy wyłącznie w pamięci ram, który działa jako interfejs do komunikacji z jądrem systemu np `/proc` `/sys`

--- 

### lista zamontowanych systemów plików 
lsblk: 

    NAME        MAJ:MIN RM   SIZE RO TYPE MOUNTPOINTS
    nvme1n1     259:0    0 476.9G  0 disk
    ├─nvme1n1p2 259:1    0    45G  0 part [SWAP]
    └─nvme1n1p3 259:2    0 431.4G  0 part /
    nvme0n1     259:3    0 931.5G  0 disk
    ├─nvme0n1p1 259:4    0   350M  0 part
    ├─nvme0n1p2 259:5    0   128M  0 part
    └─nvme0n1p3 259:6    0   931G  0 part

df -hT

    Filesystem     Type      Size  Used Avail Use% Mounted on
    dev            devtmpfs   16G     0   16G   0% /dev
    run            tmpfs      16G  1.5M   16G   1% /run
    efivarfs       efivarfs  184K  173K  6.9K  97% /sys/firmware/efi/efivars
    /dev/nvme1n1p3 ext4      424G  215G  188G  54% /
    tmpfs          tmpfs      16G   22M   16G   1% /dev/shm
    none           tmpfs     1.0M     0  1.0M   0% /run/credentials/systemd-journald.service
    tmpfs          tmpfs      16G   80K   16G   1% /tmp
    none           tmpfs     1.0M     0  1.0M   0% /run/credentials/getty@tty1.service
    tmpfs          tmpfs     3.2G  500K  3.2G   1% /run/user/1000



### które z punktów montażowych dają dostęp do instancji pseudo systemów plików 

* /proc - daje wgląd w działające procesy
* /sys - pokazuje obiekty jądra
* /dev - daje pliki reprezentujace urządzenia
* /run /tmpfs - jest do przechowywania danych ulotnych 

### znaczenie atrubutów:
* `relatime` (relativce access time) - aktualizuje zcas ostatniego dostępu do pliku (atime) tylko gdy poprzedni czas dostępu jest starszy niż czas modyfikacji (mtime) lub zmiany statuzu (ctime)
* `noexec` (no execution) - blokuje możlilwość bezpośredniego wykonywania pliku na zamontowanym ysstemie plików 
* `nodev` (no devices) - pododuje ze pliki w tym systemie plikóœ nie są interpretowane jako urządzenia 

### scenariusz gdy ich zastosowanie jst pożądane 
* realtime - pozwala oszczędzać cykle zapisu, dzięki czemu wydłużamy żywotnośc pendrive
* noexec - daje bezpoeczeństwo gdy podłączamy pendrive do nezaufanych komputerów 
* nodev - daje bezpieczoństwo. jeśli atakujacy utworzy na pendrive plik urządzenai który wskazuje na dysk twardy lub pamięć ram to mógłby nadpisać so lub wygiągnąć hasłą z pamięci 