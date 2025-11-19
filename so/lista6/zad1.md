# zad 1

---

* `tożsamość` - 

---

sudo chown root:root zad1           // właścicielem pliku jest root
sudo chmod u+s zad1                 // ustawia set-user-id dla usera (włąściciela), więc program działa z uid właściceila pliku, czyli root

dzięki nim odpalimy program przez zwykłego użytkonwnika z uprawnieniami roota

`ruid` = kto uruchomił
`euid` = z jamimi uprawnieniami działamy
`suid` = do jakich uprawnień możemy wrócić

sestuid(uid): ustaiwa, reuid = euid = suid = uid

* a - setuid(2000) : jako proces uprzywilejowany (euid = 0) wustawia real, efective i saved uid na 2000, czyli trwale porzuca uid = 0

* b - setreuid(-1, 2000): nie zmienia real uid
