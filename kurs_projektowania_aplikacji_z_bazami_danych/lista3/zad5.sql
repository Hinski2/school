-- tworzenei tabeli
if object_id('SalesLT.history') is not null 
    drop table SalesLT.history;
go 

create table SalesLT.history (
    ProductID int not null,
    StandardCost money not null, 
    ListPrice money not null, 
    ChangedAt datetime2 not null default sysdatetime() 
)


-- trigger
if object_id('SalesLT.trg') is not null 
    drop trigger SalesLT.trg;
go 

create trigger SalesLT.trg 
on SalesLT.Product 
after insert, update, delete
as begin
    -- insert
    insert into SalesLT.history(ProductID, StandardCost, ListPrice)
    select i.ProductID, i.StandardCost, i.ListPrice
    from inserted i 
    left join deleted d on d.ProductID = i.ProductID
    where d.ProductID is null; -- to inserty

    -- update
    insert into SalesLT.history(ProductID, StandardCost, ListPrice)
    select i.ProductID, i.StandardCost, i.ListPrice
    from inserted i 
    join deleted d on d.ProductID = i.ProductID 
    where i.StandardCost <> d.StandardCost or i.ListPrice <> d.ListPrice

    -- delete
    insert into SalesLT.history(ProductID, StandardCost, ListPrice)
    select d.ProductID, d.StandardCost, d.ListPrice
    from deleted d 
    left join inserted i on i.ProductID = d.ProductID
    where i.ProductID is null; -- to usunięcia
end
go

-- test
declare @p1 int, @p2 int 

select @p1 = (select top(1) ProductId from SalesLT.Product order by ProductID)
select @p2 = (select top(1) ProductId from SalesLT.Product where ProductID > @p1 order by ProductID)

update SalesLT.Product set ListPrice = 42 where ProductID = @p1;
update SalesLT.Product set ListPrice = ListPrice + 1 where ProductID = @p2;

update SalesLT.Product set ListPrice = 21 where ProductID = @p1;

-- raport
select h.ProductID, h.StandardCost, h.ListPrice, 
    h.ChangedAt as valid_from, 
    coalesce(( 
        select top (1) h2.ChangedAt
        from SalesLT.history h2
        where h2.ProductID = h.ProductID and h2.ChangedAt > h.ChangedAt
        order by h2.ChangedAt),
        sysdatetime()    
    ) as valid_to -- wyszukiwanie czasu następnej zmiany
from SalesLT.history h 
order by h.ProductID, valid_from