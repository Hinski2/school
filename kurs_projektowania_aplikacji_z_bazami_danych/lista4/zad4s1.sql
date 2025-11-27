-- rodzaje blokad
    -- read uncommitted 
    -- read committed
    -- repeatable read
    -- serializable
    -- snapshot

print @@spid
drop table if exists liczby;
go
create table liczby ( liczba int );
go
insert liczby values ( 10 );
go

set transaction isolation level serializable; -- repeatable read; serializable
begin transaction

select *
from dbo.liczby 

-- select session_id, status, command, wait_type
-- from sys.dm_exec_requests 
-- where session_id = 87

-- commit;





-- read uncommitted nie załkada s locków i ignoruje x locki
-- serailizable zakłada s lcok i nie ignoruje x lock

-- s odczyt
-- x modyfikacja (insert update delete)