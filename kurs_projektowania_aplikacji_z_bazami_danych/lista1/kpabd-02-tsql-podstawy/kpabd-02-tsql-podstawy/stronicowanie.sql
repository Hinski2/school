drop table Katalog
CREATE TABLE Katalog (id int primary key, pozycja varchar(30));

declare @i int = 1;
while @i<=100
begin
	insert Katalog values(@i, 'Pozycja'+cast(@i as varchar));
	set @i=@i+1;
end

select * from Katalog

-- SQL2000
CREATE TABLE #aux (RowNumber INT IDENTITY(1,1), Pozycja VARCHAR(30))
  
INSERT #aux
SELECT Pozycja FROM Katalog ORDER BY Pozycja DESC

DECLARE @Start int = 10, @End int = 20;
SELECT Pozycja
  FROM #aux
 WHERE RowNumber > @Start AND RowNumber <= @End
  
DROP TABLE #aux;
  
GO

-- SQL2005/2008

DECLARE @Start int = 10, @End int = 20;
SELECT Pozycja
FROM (SELECT Pozycja, ROW_NUMBER() OVER (ORDER BY Pozycja DESC) AS RowNumber FROM Katalog) OnePage
WHERE RowNumber > @Start AND RowNumber <= @End
GO
  
DECLARE @Start int = 10, @End int = 20;
WITH OnePage AS
(SELECT Pozycja, ROW_NUMBER() OVER (ORDER BY Pozycja DESC) AS RowNumber FROM Katalog)
SELECT Pozycja
FROM OnePage
WHERE RowNumber > @Start AND RowNumber <= @End
GO

-- SQL2012

SELECT Pozycja
FROM Katalog
ORDER BY Pozycja DESC
OFFSET 10 ROWS
FETCH NEXT 10 ROWS ONLY
