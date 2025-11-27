set nocount on

drop table if exists liczby
go

-- tworzymy tabele z liczbami 1..60
create table liczby( nr int primary key, liczba int )
go
declare @a int
set @a=1
while ( @a<=60)
begin
  insert liczby values ( @a, @a )
  set @a=@a+1
end
go

declare @x int
set @x=10

-- dynamic - pracuje na żywej tablicy
declare c cursor for select liczba from liczby where liczba<=@x

-- static - spamiętuje tabele
-- declare c cursor static for select liczba from liczby where liczba<=@x

-- -- keyset - spamiętuje klucze, dane czyta na żywo, gdy dojdziemy do wiersza który nie istnieje status = -2
-- declare c cursor keyset for select liczba from liczby where liczba<=@x

set @x=20

open c

declare @aux int, @licznik int -- aux - obecna zmienna z kursora, licznik - iterotor do kasowania co durgego wiersza zaczynajac od 2
set @licznik=2

print 'Kolejne liczby z kursora:'
fetch next from c into @aux 

-- kazujemy co drugą liczbę
while ( @@fetch_status=0 )
begin
--   print @aux;
  print 'Liczba: '+cast(@aux as varchar)
  print 'Licznik: '+cast(@licznik as varchar)
  print ''

  delete from liczby where liczba=@licznik
  fetch next from c into @aux 
  set @licznik=@licznik+2
end

print 'Status ostatniej instrukcji fetch: ' + cast(@@fetch_status as varchar)

close c
deallocate c

select * from liczby where liczba<=10