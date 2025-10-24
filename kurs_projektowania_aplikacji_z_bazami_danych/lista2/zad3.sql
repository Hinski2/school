create or alter procedure add_reader 
    @PESEL char(11),
    @Nazwisko varchar(30),
    @Data_Urodzenia varchar(10) --yyyy-mm-dd
as 
begin
    if @PESEL not like '[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]' 
        throw 50042, 'PESEL must have 11 digits', 1;

    if exists (select 1 from Czytelnik where PESEL = @PESEL)
        throw 50021, 'User with this pesel already exists', 1 

    if len(trim(@Nazwisko)) < 2 
        throw 50420, 'last name must have at least 2 characters', 1;

    if left(@Nazwisko, 1) COLLATE Polish_100_CS_AS <> upper(left(@Nazwisko, 1)) COLLATE Polish_100_CS_AS
        throw 54200, 'last name must start with a capital letter', 1;

    declare @du date = try_convert(date, @Data_Urodzenia)
    if @du is null 
        throw 54020, 'birth date must be in format yyyy-mm-dd', 1;

    INSERT INTO dbo.Czytelnik(PESEL, Nazwisko, Data_Urodzenia)
        VALUES (@PESEL, @Nazwisko, @du);
end
go

exec add_reader
    @PESEL = '11111111115',
    @Nazwisko= 'Łowalski',
    @Data_Urodzenia = '2004-12-20'

select * 
from Czytelnik