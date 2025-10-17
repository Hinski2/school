Select Distinct a.City 
From SalesLT.SalesOrderHeader sh 
Join SalesLT.Address a On sh.ShipToAddressID = a.AddressID 
Where sh.ShipDate Is Not Null
Order By a.City