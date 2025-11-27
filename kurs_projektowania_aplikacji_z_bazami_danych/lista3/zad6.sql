-- tworzymy tabele 
if object_id('dbo.brand_approvals') is not null 
    drop table dbo.brand_approvals;
go

CREATE TABLE dbo.brand_approvals(
    brand_id INT IDENTITY PRIMARY KEY,
    brand_name VARCHAR(255) NOT NULL
);
go

if object_id('dbo.brands') is not null 
    drop table dbo.brands;
go

create table dbo.brands (
    brand_id int identity primary key,
    brand_name varchar(255) not null
);
go

-- tworzymy widok
if object_id('dbo.vw_brands') is not null 
    drop view dbo.vw_brands; 
go

-- widok: nazwane i zapisane zapytanie select, które mozna użyać jak tabeli
CREATE VIEW dbo.vw_brands 
AS
SELECT
    brand_name, 
    'Approved' approval_status -- doklejamy kolumne ze stałą etykietą Approved 
FROM
    dbo.brands
UNION -- scala wyniki i usówa duplikaty z drógiego selecta
SELECT
    brand_name,
    'Pending Approval' approval_status
FROM
    dbo.brand_approvals;
go

-- tworzymy trigger
if object_id('dbo.trg_vw_brands') is not null 
    drop trigger dbo.trg_vw_brands;
go

CREATE TRIGGER dbo.trg_vw_brands 
ON dbo.vw_brands
INSTEAD OF INSERT
AS
BEGIN
    SET NOCOUNT ON;
    INSERT INTO dbo.brand_approvals ( 
        brand_name
    )
    SELECT
        i.brand_name
    FROM
        inserted i
    WHERE -- wstawiamy do brand_approvals jeśli jeszcze nei zaakceptowaliśmy w brands
        i.brand_name NOT IN (
            SELECT 
                brand_name
            FROM
                dbo.brands
        );
END
go

-- test
INSERT INTO dbo.vw_brands(brand_name)
VALUES('Eddy Merckx');
go

SELECT
	brand_name,
	approval_status
FROM
	dbo.vw_brands;
go