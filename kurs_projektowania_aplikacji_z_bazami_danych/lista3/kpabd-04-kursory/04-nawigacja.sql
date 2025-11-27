set nocount on
delete from liczby
declare @x int
set @x=1
while ( @x<=11 )
begin
  insert into liczby values(@x,@x)
  set @x=@x+1
end

declare c cursor static for select liczba from liczby order by 1
declare @i int
declare @t int

open c

set @i=1
while ( @i<=(@@cursor_rows+1)/2 )
begin
  fetch absolute @i from c into @x
  print @x
  set @t=@@cursor_rows-@i+1 
  fetch absolute @t from c into @x
  print @x
  set @i=@i+1
end

close c

print ''

open c

set @i=1
while ( @i<=(@@cursor_rows+1)/2 )
begin
  fetch absolute @i from c into @x
  print @x
  set @t=-@i 
  fetch absolute @t from c into @x
  print @x
  set @i=@i+1
end

close c


deallocate c

