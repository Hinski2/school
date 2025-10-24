declare @tablica table(klucz int not null primary key, wartosc varchar(20))
declare @i int

set @i=0
while ( @i<10 )
begin
  insert into @tablica(klucz, wartosc) values(@i, NULL)
  set @i=@i+1
end

-- wypisanie tablicy
select * from @tablica

declare @indeks int
set @indeks=5

-- przypisanie wartosci 'gosia' elementowi o indeksie 5
update @tablica set wartosc='gosia' where klucz=@indeks

-- pobranie do zmiennej wartosci elementu o indeksie 5
declare @element varchar(20)
set @element=(select wartosc from @tablica where klucz=@indeks)
select @element

-- pobranie rozmiaru tablicy
declare @rozmiar int
set @rozmiar=(select count(klucz) from @tablica)
select @rozmiar