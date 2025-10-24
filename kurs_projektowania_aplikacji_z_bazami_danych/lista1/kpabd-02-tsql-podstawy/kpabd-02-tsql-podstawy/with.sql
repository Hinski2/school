-- http://msdn.microsoft.com/en-us/library/ms175972.aspx

-- DEMO 1

WITH Wypozyczenie_CTE(Czytelnik_ID, Egzemplarz_ID, Rok)
AS
(
	SELECT Czytelnik_ID, Egzemplarz_ID, YEAR(Data) Rok
	FROM Wypozyczenie
)
SELECT Czytelnik_ID, COUNT(Egzemplarz_ID), Rok
FROM Wypozyczenie_CTE
GROUP BY Rok, Czytelnik_ID


-- DEMO 2

DROP TABLE IF EXISTS Pracownik;
GO


CREATE TABLE Pracownik
(
	PracownikID int primary key,
	KierownikID int,
	Nazwisko varchar(30)
);
GO

insert into Pracownik values(1, null, 'Godfather');
insert into Pracownik values(2, 1, 'BigBoss1');
insert into Pracownik values(3, 1, 'BigBoss2');
insert into Pracownik values(4, 2, 'Boss1');
insert into Pracownik values(5, 2, 'Boss2');
insert into Pracownik values(6, 3, 'Boss3');
insert into Pracownik values(7, 3, 'Boss4');
insert into Pracownik values(8, 4, 'Worker1');
insert into Pracownik values(9, 5, 'Worker2');
insert into Pracownik values(10, 6, 'Worker3');
insert into Pracownik values(11, 7, 'Worker4');

WITH Przelozony(PracownikID, KierownikID, Nazwisko, Poziom) AS
(
	SELECT PracownikID, KierownikID, Nazwisko, 0 FROM Pracownik WHERE KierownikID IS NULL
	UNION ALL
	SELECT prac.PracownikID, prac.KierownikID, prac.Nazwisko, Poziom + 1 FROM Pracownik prac
        INNER JOIN Przelozony prze
        ON prac.KierownikID = prze.PracownikID
)
SELECT PracownikID, KierownikID, Nazwisko, Poziom FROM Przelozony
ORDER BY Poziom