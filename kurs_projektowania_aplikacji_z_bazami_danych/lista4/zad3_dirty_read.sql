S1: 
    if object_id('dbo.test') is not null 
        drop table dbo.test;
    
    create table dbo.test(
        Id int primary key,
        Val int,
    );

    insert dbo.test values(0, 0);


    begin tran;
    update dbo.test 
    set Val = 42
    where id = 1

S2: 
    set transaction isolation level read uncommitted;
    select val from dbo.test where id = 1;

S1:
    rollback;