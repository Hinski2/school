DECLARE @treshold MONEY = 50000;
DECLARE @priotityOUT INT;
DECLARE @SQLstring NVARCHAR(255);
DECLARE @ParmDefinition nvarchar(500);
SET @ParmDefinition = N'@priotityOUT decimal(10,2) OUTPUT, @treshold int';
SET @SQLstring = N'select @priotityOUT = count(*) from SalesLT.SalesOrderHeader o where o.TotalDue>=@treshold';
EXEC sp_executesql @SQLstring, @ParmDefinition, @priotityOUT OUTPUT, @treshold;
SELECT @priotityOUT, @treshold;
