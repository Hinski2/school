create type czytelnik_id_table as table (
    czytelnik_id int PRIMARY key
);
go


create or alter procedure sum_days_for_readers 
    @Readers czytelnik_id_table readonly
as 
begin 
    select r.czytelnik_id, coalesce(sum(w.Liczba_Dni), 0) sum_days 
    from @Readers r  
    left join Wypozyczenie w on w.Czytelnik_ID = r.czytelnik_id
    group by r.czytelnik_id
end 
go 

declare @ids czytelnik_id_table 
insert into @ids values (1), (2), (3), (44);
exec sum_days_for_readers @Readers = @ids