dbcc freeproccache -- wyczyszczenie buffowa wykonywania planu

if object_id('Ksiazka.IX') is not null 
    drop index ix; 

create nonclustered index IX on Ksiazka.Ksiazka_ID;

select * 
from Egzemplarz e 
join Ksiazka k on e.Ksiazka_ID = k.Ksiazka_ID;
go