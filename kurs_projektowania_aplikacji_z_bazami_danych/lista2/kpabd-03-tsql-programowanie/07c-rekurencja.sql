-- 1 --
drop procedure if exists Nested
go
create procedure Nested
as
begin
  print @@nestlevel
  exec Nested
end
go
exec Nested
go

-- 2 --
drop procedure if exists Silnia
go
-- rekurencyjna silnia, parametry <=12 (ograniczeniem jest rozmiar inta)
create procedure Silnia @argument int, @wynik int output
as
  declare @nargument int
  declare @nwynik int
begin
  if ( @argument < 0 or @argument>12 ) return -1
  if ( @argument>1 )
  begin
    set @nargument=@argument-1
    set @wynik=@argument*@wynik
    exec Silnia @argument=@nargument, @wynik=@wynik output
  end
end
go
declare @wynik int
declare @result int
declare @i int
set @i=0
while ( @i<20 )
begin
  set @wynik=1
  exec @result=Silnia @i, @wynik output
  if ( @result=-1 ) return
  print cast( @i as varchar ) + '! = ' + cast( @wynik as varchar )
  set @i=@i+1
end
go

-- 3 --
-- wymieniamy typ int na decimal(38,0), wtedy maksymalnie mo¿emy policzyæ 32!
drop procedure if exists SuperSilnia
go
-- rekurencyjna supersilnia, parametry <=32 (ograniczeniem jest g³êbokoœæ stosu)
create procedure SuperSilnia @argument int, @wynik decimal(38,0) output
as
  declare @nargument decimal(38,0)
  declare @nwynik decimal(38,0)
begin
  if ( @argument < 0 or @argument>32 ) return -1
  if ( @argument>1 )
  begin
    set @nargument=@argument-1
    set @wynik=@argument*@wynik
    exec SuperSilnia @argument=@nargument, @wynik=@wynik output
  end
end
go
declare @wynik decimal(38,0)
declare @result int
declare @i int
set @i=0
while ( @i<50 )
begin
  set @wynik=1
  exec @result=SuperSilnia @i, @wynik output
  if ( @result=-1 ) return
  print cast( @i as varchar ) + '! = ' + cast( @wynik as varchar(50) )
  set @i=@i+1
end
go

-- 4 --
-- silnia w wersji iteracyjnej
drop procedure if exists IterSilnia
go
create procedure IterSilnia @argument int, @wynik decimal(38,0) output
as
begin
  if ( @argument < 0 or @argument>33 ) return -1
  set @wynik=1
  while ( @argument>1 )
  begin
    set @wynik=@wynik*@argument
    set @argument=@argument-1
  end
end
go
declare @wynik decimal(38,0)
declare @result int
declare @i int
set @i=0
while ( @i<50 )
begin
  set @wynik=1
  exec @result=IterSilnia @i, @wynik output
  if ( @result=-1 ) return
  print cast( @i as varchar ) + '! = ' + cast( @wynik as varchar(50) )
  set @i=@i+1
end
go