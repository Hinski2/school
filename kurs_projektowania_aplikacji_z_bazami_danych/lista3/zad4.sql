if object_id('SalesLT.trg') is not null
    drop trigger SalesLT.trg;
go

create trigger SalesLT.trg
on SalesLT.Customer
after insert, update
as begin
    if trigger_nestlevel() > 1 return; -- zatrzymanie rekursji

    update c
    set ModifiedDate = sysdatetime()
    from SalesLT.Customer c
    join inserted i on i.CustomerID = c.CustomerID;
end
go

-- przed 
select top (1) CustomerID, ModifiedDate
from SalesLT.Customer
order by CustomerID;

-- zmiana 
update SalesLT.Customer
set FirstName = FirstName
where CustomerID = (
    select top(1) CustomerID
    from SalesLT.Customer
    order by CustomerID
)

-- po
select top (1) CustomerID, ModifiedDate
from SalesLT.Customer
order by CustomerID;