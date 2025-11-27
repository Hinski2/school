-- setup
if object_id('dbo.test') is not null
    drop table dbo.test 

create table dbo.test(
    Id int primary key, 
    val int
);
go

-- procedura wewnętrzna
create or alter procedure dbo.a 
    @Id int,
    @Val int, 
    @Fail bit
as begin
    declare @t int = @@trancount;
    if @t > 0
        save tran SavePoint
    else 
        begin transaction

    begin try
        insert into dbo.test(Id, Val) 
        values(@Id, @Val);

        if @fail = 1
            throw 50042, 'fail', 1;
        if @t = 0
            commit 
    end try 
    begin catch 
        if @t = 0 
            rollback; 
        else if XACT_STATE() <> -1 -- stan -1 to aktywna tranzakcja w tanie niekomitowalnym
            rollback transaction SavePoint;

        throw;
    end catch
end
go

-- procedura zewnętrzna 
create or alter procedure dbo.b 
as begin 
    begin tran 

    begin try 
        exec dbo.a @Id = 1, @Val = 10, @Fail = 0;
        exec dbo.a @Id = 2, @Val = 10, @Fail = 1;
        commit
    end try
    begin catch
        rollback;
        throw; 
    end catch 
end
go

exec dbo.b;
go

select * from dbo.test