
create table Product (
    Id uniqueidentifier primary key,
    Name nvarchar(100),
    Description nvarchar(max),
    PictureUrl nvarchar(max),
    
    PriceAmount decimal(18,2),
    PriceCurrency nvarchar(10),

    Unit INT, 
    Status INT
);

create table Cart (
    Id uniqueidentifier primary key
);

CREATE TABLE CartItem (
    CartId uniqueidentifier references Cart(Id), -- fk do koszyka
    
    ProductId uniqueidentifier,
    Name nvarchar(100),
    Quantity decimal(18,2),

    PriceAmount decimal(18,2),
    PriceCurrency nvarchar(10)
);
GO