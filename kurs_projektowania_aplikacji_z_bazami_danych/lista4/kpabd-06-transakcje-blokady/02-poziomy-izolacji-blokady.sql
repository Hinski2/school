-- rodzaje blokad

USE Test;

drop table if exists liczby;
go
create table liczby ( liczba int );
go
insert liczby values ( 10 );
go

-- 1 --
set transaction isolation level repeatable read;
begin transaction

-- w drugim po��czeniu robimy update: update liczby set liczba=4
-- ogl�damy blokady: sp_lock

select * from liczby

-- ponownie w drugim po��czeniu robimy update: update liczby set liczba=4
-- ogl�damy blokady: sp_lock

commit

-- 2 --
set transaction isolation level serializable;

insert liczby values ( 10 );

begin transaction

-- w drugim po��czeniu robimy insert: insert liczby values(151)
-- ogl�damy blokady: sp_lock

select * from liczby

-- ponownie w drugim po��czeniu robimy insert: insert liczby values(151)
-- ogl�damy blokady: sp_lock

commit

-- 3 --
-- sprawdzamy opcj� Allow Snapshot Isolation
-- ALTER DATABASE AdventureWorksLT SET ALLOW_SNAPSHOT_ISOLATION ON
set transaction isolation level snapshot;
begin transaction

select * from liczby

-- ponownie w drugim po��czeniu robimy update: update liczby set liczba=6
-- ogl�damy blokady: sp_lock

update liczby set liczba=7

select * from liczby

commit
