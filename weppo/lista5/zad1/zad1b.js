// comon js
const math = require('./b.js'); // synchroniczne
console.log(math.add(1, 1))

/*
    tak możliwe jest tworzenie cyklicznych zależności między modułami
    comonJs:
        gdy cykl jest wykrywany js robi częściowy eksport tylko 
        może to prowadzić do problemów i niepełnych eksportów
        możemy napotkać undefined behaviours gdy będziemy sie odwoływali drzeczy kóre nie zostały jeszcze zaimportowane

    ES modules:
        dzięki statycznej analizie importów / eksportoów działa lepiej
        możemy dostać undefined, gdy odwołujemy się do zmiennych które jeszcze nie zostały zainicjowane 
*/