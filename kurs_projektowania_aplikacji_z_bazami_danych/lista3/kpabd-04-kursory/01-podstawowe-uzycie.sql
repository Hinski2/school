drop table if exists produkty;
go
create table produkty ( id int, nazwa varchar(20), ilosc int )
go
set nocount on;
insert produkty values ( 1, 'Banan', 20 )
insert produkty values ( 2, 'Kiwi', 30 )
insert produkty values ( 3, 'Mandarynka', 16 )
set nocount off;
go

declare c_produkty cursor for select nazwa,ilosc from produkty
declare @nazwa varchar(200), @ilosc int

open c_produkty
fetch next from c_produkty into @nazwa, @ilosc
while ( @@fetch_status=0 )
begin
  print cast( @nazwa as char(10) )+' '+cast( @ilosc as char(10) )
  fetch next from c_produkty into @nazwa, @ilosc
end
close c_produkty

open c_produkty
fetch next from c_produkty into @nazwa, @ilosc
while ( @@fetch_status=0 )
begin
  print cast( @nazwa as char(10) )+' '+cast( @ilosc as char(10) )
  fetch next from c_produkty into @nazwa, @ilosc
end
close c_produkty

deallocate c_produkty
go