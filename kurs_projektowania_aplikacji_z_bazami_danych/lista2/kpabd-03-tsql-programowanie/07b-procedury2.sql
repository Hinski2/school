-- przykład wykorzystania resultsetu wewnątrz kodu T-SQL https://stackoverflow.com/questions/861187/how-do-i-use-the-results-of-a-stored-procedure-from-within-another
-- https://docs.microsoft.com/en-us/sql/relational-databases/native-client-odbc-stored-procedures/processing-stored-procedure-results?view=sql-server-ver15
create or alter procedure sp_czytelnicy
as begin
select Czytelnik_ID, PESEL, Nazwisko from Czytelnik
end;
go

declare @aux table (
    id int identity(1,1),
    Czytelnik_ID int,
    PESEL char(11),
	Nazwisko varchar(max)
	)

declare @result int

insert into @aux (Czytelnik_ID,PESEL,Nazwisko)
exec @result = sp_czytelnicy

select * from @aux
go
