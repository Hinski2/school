declare c cursor static for select * from egzemplarz order by 1

open c
select @@cursor_rows
fetch c
while ( @@fetch_status=0 ) fetch c 
close c
deallocate c

