drop table if exists liczby;
go
create table liczby ( liczba int )
go
declare @i int
set @i=1
while @i<100
begin
  insert liczby values( @i )
  set @i=@i+1
end
go

-- 1 --
drop procedure if exists sp_liczby
go
create procedure sp_liczby @max int = 10
as
begin
  select liczba from liczby
  where liczba<=@max
end
go
exec sp_liczby @max=3
exec sp_liczby
go

-- 2 --
drop procedure if exists sp_statystyka
go
create procedure sp_statystyka @max int output, @min int output, @aux int output
as
begin
  set @max=( select max(liczba) from liczby )
  set @min=( select min(liczba) from liczby )
  set @aux=10
end
go
declare @max int, @min int, @aux2 int
exec sp_statystyka @max output, @min output, @aux=@aux2 output
select @max 'Max', @min 'Min', @aux2
go
