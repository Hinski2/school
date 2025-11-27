
-- -- dirty read
set transaction isolation level read uncommitted;
begin tran 

select Val 
from dbo.test 
where id = 1;
commit;

-- -- non repeatable rad
-- set transaction isolation level read uncommitted;
-- begin tran 
-- update dbo.test 
-- set val = 42 
-- where id = 1
-- commit;


-- -- phantom read
-- set transaction isolation level read uncommitted;
-- begin tran 
-- insert dbo.test(Id, Val) values (2, 1000)
-- commit;
