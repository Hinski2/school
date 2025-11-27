S1: 
    if object_id('dbo.test') is not null 
        drop table dbo.test;
    
    create table dbo.test(
        Id int primary key,
        Val int,
    );
    
    insert dbo.test values(0, 0);


    set transaction isolation lvl read uncommitted
    begin tran;

    select * from dbo.test 

S2: 
    insert dbo.test(Val) values (42)
    commit;

S1:
    select * from dbo.test