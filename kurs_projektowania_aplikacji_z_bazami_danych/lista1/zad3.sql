select a.city, COUNT(distinct c.CustomerID) NumberOfCustomers, COUNT(distinct c.SalesPerson) NumberOfSalesPerson
from SalesLT.Address a 
join SalesLT.CustomerAddress ca on a.AddressID = ca.AddressID
join SalesLT.Customer c on ca.CustomerID = c.CustomerID 
group by a.city
order by NumberOfCustomers desc, NumberOfSalesPerson desc 
