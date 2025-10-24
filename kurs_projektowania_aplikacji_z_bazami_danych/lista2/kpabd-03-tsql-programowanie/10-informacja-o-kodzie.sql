sp_helptext Silnia
go

create procedure TajnaSilnia @argument int, @wynik int output
with encryption
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

sp_helptext TajnaSilnia
go

-- Poni¿szy kod wypisuje info, która procedura jest zaszyfrowana i ewentualnie jej tekst
select o.name, o.id, encrypted, compressed, text
from syscomments c join sysobjects o on o.id=c.id
where o.id=object_id('Silnia') or o.id=object_id('TajnaSilnia')