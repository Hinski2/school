# zad 1

---

* `tożsamość` - zestaw identyfikatorów procesu i grup: ruid, euid, suid

---

sudo chown root:root zad1           // właścicielem pliku jest root
sudo chmod u+s zad1                 // ustawia set-user-id dla usera (włąściciela), więc program działa z uid właściceila pliku, czyli root

dzięki nim odpalimy program przez zwykłego użytkonwnika z uprawnieniami roota

`ruid` = kto uruchomił
`euid` = z jamimi uprawnieniami działamy
`suid` = do jakich uprawnień możemy wrócić

sestuid(uid):
* dla uprzywilejowanego: ustaiwa, reuid = euid = suid = uid
* dla zwyklłego może ustawić uid tylko na swój własny

seteruid(ruid, euid):
* -1 znaczy nie zmieniaj tego 
* ustaiwia osobno zienić ruid i euid
* używany by tymczasowo zamienić sie ruid <-> euid

seteuid(euid):
* zmiania tylko effective uid
* używany by tymczasowo zmienić uprawinienia z którymi działamy

setresuid(ruid, euid, suid):
* -1 znaczy nie zmieniaj tego
* pozwala na zmiana ruid, euid, suid

* a - setuid(2000) : jako proces uprzywilejowany (euid = 0) wustawia real, efective i saved uid na 2000, czyli trwale porzuca uid = 0

* b - setreuid(-1, 2000): nie zmienia real uid


### Czy proces z tożsamością ruid=0, euid=1000, suid=1000 jest uprzywilejowany?

nie ten proces nie jest uprzywilejowany, bo o tym czy proces jest rootem przy sprawdzaniu dostępu decyfuje euid. 

to że ruid = 0. znacza tylko ze prawdzimy włąscicielem proces ujest root

w unix proce niuprzywilejoany (ten z euid != 0) moze ustawić euid na:
* swój ruid
* swój suid
* bieżący euid