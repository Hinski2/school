-- tworzenie tabeli
if object_id('dbo.specimen') is not null -- egzemplaże
    drop table dbo.specimen;
go

if object_id('dbo.book') is not null  -- książki
    drop table dbo.book;
go

create table dbo.book (
    id int identity primary key
);
go

create table dbo.specimen (
    id int identity primary key, 
    bookID int not null references dbo.book(id)
)

-- tworzenie triggera
if object_id('dbo.trg') is not null 
    drop trigger dbo.trg;
go 

create trigger dbo.trg 
on dbo.specimen
after insert, update 
as begin
    if exists (
        select 1 
        from dbo.specimen s 
        join ( 
            select distinct bookID from inserted where bookID is not null 
        ) t on t.bookID = s.bookID
        group by s.bookID 
        having count(*) > 5
    )
    begin
        rollback transaction
        print 'book may have at most 5 specimens' 
    end
end;
go

-- test
insert into dbo.book default values;

insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
insert into dbo.specimen(bookID) values (1);
go

select * 
from dbo.specimen
