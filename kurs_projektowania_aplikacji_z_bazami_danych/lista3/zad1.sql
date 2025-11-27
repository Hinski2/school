if object_id('SalesLT.ProductBackup') is not null
    drop table SalesLT.ProductBackup;
go 

select top (0) *
into saleslt.ProductBackup
from saleslt.product;
go

-- standard
declare @t1 datetime2 = sysdatetime();

insert into saleslt.productbackup (name, productnumber, color, standardcost, listprice, sellstartdate, rowguid, modifieddate)
select name, productnumber, color, standardcost, listprice, sellstartdate, rowguid, modifieddate
from saleslt.product;

declare @t2 datetime2 = sysdatetime();

print 'standard: ' + cast(datediff(ms, @t1, @t2) as varchar(20))
go

-- cursor

truncate table saleslt.productbackup;

declare
    @productid int,
    @name nvarchar(50),
    @productnumber nvarchar(25),
    @color nvarchar(15),
    @standardcost money,
    @listprice money,
    @sellstartdate datetime,
    @rowguid uniqueidentifier,
    @modifieddate datetime;


declare c cursor fast_forward for
select productid, name, productnumber, color, standardcost, listprice, sellstartdate, rowguid, ModifiedDate
from saleslt.product;

declare @t3 datetime2 = sysdatetime();

open c;
fetch next from c
into @productid, @name, @productnumber, @color, @standardcost, @listprice, @sellstartdate, @rowguid, @modifieddate;

while @@fetch_status = 0
begin
    insert into saleslt.productbackup (name, productnumber, color, standardcost, listprice, sellstartdate, rowguid, modifieddate)
    values (@name, @productnumber, @color, @standardcost, @listprice, @sellstartdate, @rowguid, @modifieddate);

    fetch next from c
    into @productid, @name, @productnumber, @color, @standardcost, @listprice, @sellstartdate, @rowguid, @modifieddate;
end

close c;
deallocate c;

declare @t4 datetime2 = sysdatetime();

print 'cursor: ' + cast(datediff(ms, @t3, @t4) as varchar(20))
go