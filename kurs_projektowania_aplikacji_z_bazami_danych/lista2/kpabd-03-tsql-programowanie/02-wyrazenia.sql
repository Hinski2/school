-- WAITFOR
DROP TABLE IF EXISTS Numbers;
CREATE TABLE Numbers(Number INT);
declare @x int
select @x=2
insert into Numbers values( @x );
print 'Wstawiono...'
waitfor delay '00:00:05'
insert into Numbers values( @x+2 );
print 'Wstawiono...'
GO

-- IF..ELSE
if EXISTS( select * from SalesLT.SalesOrderHeader) print('S¹ zamówienia')
else print('Nie ma ¿adnych zamówieñ')
GO

-- WHILE
declare @y int
select @y=0
while ( @y<10 )
begin
  print @y
  if ( @y=5 ) break
  set @y=@y+1
end

-- CASE
select Tytul as Tytu³, Cena, [Cena jest]=CASE
	when Cena<40.00 then 'Niska'
	when Cena between 40.00 and 80.00 then 'Przystêpna'
	when Cena>80 then 'Wysoka'
	else 'Nieznana'
	end
from Ksiazka

select p.Name, Kategoria=CASE c.Name
	when 'Bikes' then 'Rowery'
	when 'Brakes' then 'Hamulce'
	when 'Chains' then '£añcuchy'
	when 'Gloves' then 'Rêkawice'
	else 'Inne'
	end
FROM SalesLT.Product p JOIN SalesLT.ProductCategory c ON p.ProductCategoryID=c.ProductCategoryID
-- Jak powy¿sze nale¿y w³aœciwie zrobiæ?

-- NULLIF
-- przydatne, kiedy chcemy pomin¹æ jak¹œ wartoœæ w funkcjach agreguj¹cychk
-- wpisaæ 170, ¿eby zobaczyæ efekt
select
avg( nullif( Weight, 0 ) ) as [Œrednia waga],
min( nullif( Weight, 0 ) ) as [Minimalna waga]
from SalesLT.Product
-- Poni¿ej aby sprawdziæ dzia³anie AVG
select avg(Weight) from SalesLT.Product where ProductID<710
select * from SalesLT.Product

-- ISNULL
-- pozwala na nadawanie wartoœci domyœlnych tam, gdzie jest NULL
SELECT Name, ISNULL(ThumbnailPhotoFileName, 'http://jakasdomyslnafocia.pl/') FROM SalesLT.Product
-- mo¿na te¿ umieszczaæ podzapytania, np.: isnull( price, ( select MIN(price) from ceny ) )
