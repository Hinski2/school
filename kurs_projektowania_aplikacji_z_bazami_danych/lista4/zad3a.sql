if object_id('dbo.test') is not null 
        drop table dbo.test;
    
create table dbo.test(
    Id int primary key,
    Val int
);

insert dbo.test values(1, 100);

-- dirty read
begin tran;
update dbo.test 
set Val = 42
where id = 1

waitfor delay '00:00:05';
rollback
commit;

-- -- nonrepetable read 
-- set transaction isolation level read uncommitted
-- begin tran

-- select val
-- from dbo.test
-- where id = 1;

-- waitfor delay '00:00:05';

-- select val from dbo.test where id = 1;
-- commit;

-- -- phantom read
-- set transaction isolation level read uncommitted
-- begin tran;

-- select * from dbo.test 

-- waitfor delay '00:00:05';

-- select * from dbo.test 
-- commit;