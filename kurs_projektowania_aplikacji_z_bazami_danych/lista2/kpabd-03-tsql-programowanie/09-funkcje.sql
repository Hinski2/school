-- 1 --

drop function if exists fn_srednia
go

create function fn_srednia(@customerID int) returns decimal(10,2)
begin
  return (select avg(TotalDue) from SalesLT.SalesOrderHeader WHERE CustomerID=@customerID)
end
go

select dbo.fn_srednia(29660) [Œrednia cena]
select dbo.fn_srednia(29975) [Œrednia cena]
go

-- 2 --

DROP FUNCTION IF EXISTS Siedem;
GO
CREATE FUNCTION Siedem ( @x INT = 7 ) RETURNS INT
BEGIN
   RETURN ( @x )
END
GO

SELECT dbo.Siedem(DEFAULT)
GO

-- 3 --

drop function if exists fn_silnia
GO
create function fn_silnia(@n int) returns decimal(38,0)
begin
  if ( @n<0 or @n>31 ) return 0
  if ( @n=0 or @n=0 ) return 1
  return @n*dbo.fn_silnia(@n-1)
end
go
select dbo.fn_silnia(31) [Silnia 31]
go

-- 4 --

drop function if exists fn_tablicasilni
go

create function fn_tablicasilni(@ile int) returns @tablica table(liczba decimal(38,0))
begin
  if ( @ile>30 ) set @ile=30
  declare @i int
  set @i=1
  while ( @i<=@ile )
  begin
    insert into @tablica select dbo.fn_silnia(@i)
    set @i=@i+1
  end
  return
end
go

select * from fn_tablicasilni(40)
go

-- 5 --
drop table if exists liczby 
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

drop function if exists funkcja
go
create function funkcja(@max int) returns table
return (select * from liczby where liczba<=@max)
go
select * from funkcja(3)
go