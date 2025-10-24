declare @x int, @s varchar(10)

set @x=10
set @s='2'

print @x+@s
--print 'n'+@x
GO


declare @imie varchar(20), @nazwisko varchar(20)

-- poprawnie
select @imie=FirstName, @nazwisko=LastName from SalesLT.Customer where CustomerID=7
print @imie+' '+@nazwisko

-- tutaj zostan¹ przypisane dane z ostatniego wiersza (przyda³oby siê sortowanie, ¿eby nad tym panowaæ)
select @imie=FirstName, @nazwisko=LastName from SalesLT.Customer
print @imie+' '+@nazwisko

-- trzeba równie¿ przypilnowaæ, ¿eby by³y przypisane jakieœ wartoœci. jeœli w wyniku zapytania nie bêdzie
-- zwrócona ¿adna wartoœæ zmienna zachowa dotychczasow¹ wartoœæ
set @imie='Teofil'
set @nazwisko='Szczerbaty'
select @imie=FirstName, @nazwisko=LastName from SalesLT.Customer where CustomerID=20
print @imie+' '+@nazwisko

-- analizujemy poni¿sze dwa przyk³ady
select @nazwisko=LastName from SalesLT.Customer
print @nazwisko
select @nazwisko=(select MIN(LastName) from SalesLT.Customer)
print @nazwisko
GO