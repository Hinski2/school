drop table IF EXISTS ranking;
drop table IF EXISTS uzytkownik;
GO

create table uzytkownik
(
	id int primary key identity,
	nazwisko varchar(30)
);
GO

create table ranking
(
	id int primary key identity,
	uzytkownik int references uzytkownik,
	punkty int,
	czas int
);
GO

insert uzytkownik values('kowalski');
insert uzytkownik values('malinowski');
insert uzytkownik values('drewniak');
insert uzytkownik values('miauczyñski');
insert uzytkownik values('rambo');

insert ranking values(1, 20, 235);
insert ranking values(2, 30, 435);
insert ranking values(2, 30, 635);
insert ranking values(3, 10, 160);
insert ranking values(3, 20, 210);
GO

select * from uzytkownik
select * from ranking
GO

--declare @max int
--select @max = max(punkty) from ranking

MERGE ranking AS r
USING (SELECT id,nazwisko FROM uzytkownik) AS u
ON r.uzytkownik = u.id
WHEN MATCHED AND r.punkty = (select max(punkty) from ranking) THEN DELETE
WHEN MATCHED AND r.czas > 150 THEN UPDATE SET r.punkty = r.punkty + 10
WHEN NOT MATCHED THEN
INSERT(uzytkownik,punkty,czas)
VALUES(u.id,0,0);
GO

select * from ranking
GO