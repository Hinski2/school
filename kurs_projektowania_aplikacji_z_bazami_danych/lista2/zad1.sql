create or alter function fn_czylelncy_min_days(@days INT) returns table 
as
return (
    select c.PESEL, count(*) no_books
    from Wypozyczenie w 
    join Czytelnik c on c.Czytelnik_ID = w.Czytelnik_ID 
    group by c.PESEL 
    having max(w.Liczba_Dni) >= @days
);
go

select * 
from fn_czylelncy_min_days(5)