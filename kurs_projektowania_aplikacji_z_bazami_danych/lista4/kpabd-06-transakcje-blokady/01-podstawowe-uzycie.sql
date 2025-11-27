USE AdventureWorksLT

-- 1 --
drop table if exists liczby;
go
create table liczby ( liczba int );
go

set implicit_transactions on
go

delete from liczby;
commit
--begin tran
insert into liczby(liczba) values(1);
insert into liczby(liczba) values(2);
insert into liczby(liczba) values(3);
rollback tran
go

select count(*) from liczby

-- 2 --
set implicit_transactions off
commit -- to jest wa¿ne - trzeba zatwierdziæ powy¿szy wiersz

delete from liczby;
insert into liczby(liczba) values(1);
begin tran
insert into liczby(liczba) values(2);
insert into liczby(liczba) values(3);
rollback tran
go

select count(*) from liczby


-- 3 --

begin transaction A
select @@trancount
begin transaction B
select @@trancount
commit tran
select @@trancount
commit tran
go

-- 4 --

begin transaction A
select @@trancount
begin transaction B
select @@trancount
rollback transaction B -- tu bêdzie b³¹d
select @@trancount
rollback tran A -- ale tu jest ok
select @@trancount
go

-- 5 --

delete from liczby
begin transaction
insert into liczby(liczba) values(1)
save transaction b
insert into liczby(liczba) values(2)
save transaction c
insert into liczby(liczba) values(3)
rollback transaction b --c
insert into liczby(liczba) values(4)
commit
go

select * from liczby
