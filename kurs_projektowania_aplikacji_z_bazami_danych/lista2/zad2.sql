-- usówam tabele

drop table if exists firstnames;
go

drop table if exists lastnames;
go

drop table if exists fldata;
go

-- tworze tabele
create table firstnames (
    id int identity primary key,
    firstname nvarchar(50) not null
);
go

create table lastnames (
    id int identity primary key,
    lastname nvarchar(50) not null
);
go 

create table fldata (
    firstname nvarchar(50) not null,
    lastname  nvarchar(50) not null,
    constraint PK_fldata primary key (firstname, lastname)
);
go

-- wypełniam tabele
insert into firstnames(firstname) values 
    ('kuba'), ('antek'), ('andrzej'), ('michał'), ('ola'), ('janek');
go 

insert into lastnames(lastname) values 
    ('ilinski'), ('kowalski'), ('krokodyl'), ('stefanski'), ('pawliczek'), ('skala')
go 

-- procedura
create or alter procedure fill_fldata @n INT 
as 
begin
    declare @no_firstnames int, @no_lastnames int, @total int; 
    select @no_firstnames = count(distinct firstname) from firstnames;
    select @no_lastnames = count(distinct lastname) from lastnames;
    set @total = @no_firstnames * @no_lastnames;

    if @n < 0 
        throw 50042, 'n must be >= 0', 1;
    if @n > @total
        throw 54200, 'n must be <= total', 2;

    delete from fldata;

    insert into fldata(firstname, lastname)
    select top (@n) f_name.firstname, l_name.lastname
    from (select distinct firstname from firstnames) f_name 
    cross join (select distinct lastname from lastnames) l_name
    order by newid() 
end
go

-- wykonanie
exec fill_fldata @n = 10;
select * 
from fldata