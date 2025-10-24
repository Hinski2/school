create type ProductIdTable as table (
    ProductId int primary key
);
go 


create or alter procedure set_discontinued 
    @ids ProductIdTable readonly,
    @when date 
as 
begin
    -- komunikat 
    DECLARE @row NVARCHAR(200); 
    declare db_cursor cursor for 
    select * 
    from (
            select concat('skipped ', p.ProductID) as msg
            from SalesLT.Product p 
            join @ids i on i.ProductId = p.ProductID
            where p.DiscontinuedDate is not null
    ) as x;

    open db_cursor
    fetch next from db_cursor into @row
    while @@fetch_status = 0 
    begin 
        print @row 
        fetch next from db_cursor into @row 
    end

    -- ustawienie
    update p
    set p.DiscontinuedDate = @when
    from SalesLT.Product p
    join @ids i on i.ProductID = p.ProductID
    where p.DiscontinuedDate is null
end
go

declare @ids ProductIdTable;
insert into @ids(ProductId) values 
(680), (706), (708), (710);

exec set_discontinued
    @ids = @ids,
    @when = '2004-12-20';

select p.ProductID, p.DiscontinuedDate
from SalesLT.Product p 