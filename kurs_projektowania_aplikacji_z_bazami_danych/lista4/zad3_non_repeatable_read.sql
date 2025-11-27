S1: 
    if object_id('dbo.test') is not null 
        drop table dbo.test;
    
    create table dbo.test(
        Id int primary key,
        Val int,
    );
    
    insert dbo.test values(0, 0);


    set transaction isolation lvl read uncommitted
    begin tran 
    select val from dbo.test where di = 1;

S2: 
    update dbo.test 
    set val = 42 
    where id = 1
    commit;

S1: 
    select val from dbo.test where di = 1;
    commit;