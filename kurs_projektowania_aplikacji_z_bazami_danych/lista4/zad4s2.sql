insert dbo.liczby values(10000) 
-- exec sp_lock - przestażały 

select session_id, status, command, wait_type
from sys.dm_exec_requests 
where session_id = @@spid
