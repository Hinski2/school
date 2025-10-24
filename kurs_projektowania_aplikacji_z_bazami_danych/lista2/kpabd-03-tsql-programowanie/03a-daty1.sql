-- Znaczenie dateformat
set dateformat mdy
go
declare @d datetime='3/4/2005'
select @d [FORMAT mdy]
select datepart( month, @d ) Miesiac
go

set dateformat dmy
go
declare @d datetime='3/4/2005'
select @d [FORMAT dmy]
select datepart( month, @d ) Miesiac
GO

-- Istota formatu ISO
set dateformat ydm
GO
declare @d datetime='20050304'
select [FORMAT mdy]=convert( datetime, @d );
select datepart( month, @d ) Miesiac
GO
set dateformat ymd
GO
declare @d datetime='20050304'
select [FORMAT dmy]=convert( datetime, @d );
select datepart( month, @d ) Miesiac
GO

-- Operacje na datach
declare @d1 datetime, @d2 datetime
set @d1='20051020'
set @d2='20051025'

select dateadd(hour, 112, @d1)
select dateadd(day, 112, @d1)

select datediff(minute, @d1, @d2)
select datediff(day, @d1, @d2)

select datename(month, @d1)
select datepart(month, @d1)

select cast(day(@d1) as varchar)+'-'+cast(month(@d1) as varchar)+'-'+cast(year(@d1) as varchar)
