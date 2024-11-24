const math = require('./b.js'); // synchroniczne
console.log(math.add(1, 1))

/*
    tak możliwe jest tworzenie cyklicznych zależności między modułami
    comonJs:
        może to prowadzić do problemów i niepełnych eksportów
    ES modules:
        działą poprawnie, ale może mieć potencjalne problemy z wydajnością gdy mamy złożone cykle
*/