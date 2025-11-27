dbcc freeproccache -- wyczyszczenie buffowa wykonywania planu

if object_id('Egzemplarz.IX') is not null 
    drop index IX on Egzemplarz;

create clustered index IX on Egzemplarz (Ksiazka_ID)

select * 
from Egzemplarz e 
join Ksiazka k on e.Ksiazka_ID = k.Ksiazka_ID;
go
