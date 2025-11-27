-- najpierw odpalamy pierwsz¹ czêœæ
set nocount on
delete from liczby
declare @x int
set @x=1
while ( @x<=10 )
begin
  insert into liczby values(@x,@x)
  set @x=@x+1
end
go

-- odpalamy teraz drug¹ czêœæ
declare c cursor dynamic for select liczba from liczby order by 1
declare @i int
declare @t int
declare @x int

open c

fetch next from c into @x
while ( @@fetch_status=0 )
begin
  print @x
    update liczby set liczba=100+@x where current of c
--  delete from liczby where current of c
  fetch next from c into @x
end

close c

deallocate c
