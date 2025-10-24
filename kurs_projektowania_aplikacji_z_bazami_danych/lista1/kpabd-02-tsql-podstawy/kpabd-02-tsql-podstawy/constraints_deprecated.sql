USE Test;
GO

-- czyszczenie
DROP TABLE IF EXISTS [dbo].[Dane];
GO
sp_unbindefault 'DT_plec'
GO
sp_unbindrule 'DT_plec'
GO
DROP RULE IF EXISTS R_plec;
GO
DROP DEFAULT IF EXISTS DF_plec
GO
sp_droptype DT_plec;
GO

-- dodajemy nowy typ
sp_addtype DT_plec, 'char(1)'
GO

-- tworzymy nowa wartoœæ domyœln¹ i now¹ regu³ê
CREATE DEFAULT DF_plec AS '?'
GO

CREATE RULE R_plec AS @value in ('m','k','?')
GO

-- tworzymy tabelkê
CREATE TABLE [dbo].[Dane] (
	[id] [int] NOT NULL PRIMARY KEY,
	[imie] [varchar] (20) NULL ,
	[nazwisko] [varchar] (30)  ,
	[pesel] [char] (11) NULL ,
	[dataurodzenia] [datetime] NULL ,
	[plec] [DT_plec]
);
GO

-- dowi¹zujemy do typu DT_plec wartoœæ domyœln¹ DF_plec i regu³ê R_plec
sp_bindefault DF_plec, 'DT_plec', FUTUREONLY
GO

sp_bindrule R_plec, 'DT_plec', FUTUREONLY
GO

-- wstawiamy dwa rekordy
INSERT INTO Dane(id, imie, nazwisko, pesel, dataurodzenia)
    VALUES(1, 'Anna', 'Deresz', '12345678901', '19500202')
INSERT INTO Dane(id, imie, nazwisko, pesel, dataurodzenia, plec)
    VALUES(2, 'Kasia', 'Ekola', '12345678901', '19500202','f')

-- zauwa¿amy, ¿e ani wartoœæ domyœlna, ani regu³a dowi¹zane uprzednio nie dzia³aj¹
-- jest to spowodowane opcj¹ FUTUREONLY
SELECT * FROM Dane
-- pucujemy tabelkê
DELETE FROM Dane

-- odwi¹zujemy od DT_plec wartoœæ domyœln¹ i regu³ê
sp_unbindefault 'DT_plec'
GO

sp_unbindrule 'DT_plec'
GO

-- dowi¹zujemy do typu DT_plec wartoœæ domyœln¹ DF_plec i regu³ê R_plec, ale bez opcji FUTUREONLY
sp_bindefault DF_plec, 'DT_plec'
GO

sp_bindrule R_plec, 'DT_plec'
GO

-- wstawiamy dwa rekordy
INSERT INTO Dane(id, imie, nazwisko, pesel, dataurodzenia)
    VALUES(1, 'Anna', 'Deresz', '12345678901', '19500202')
--INSERT INTO Dane(id, imie, nazwisko, pesel, dataurodzenia, plec)
--    VALUES(2, 'Kasia', 'Ekola', '12345678901', '19500202','f') -- bledne ze wzglêdu na 'f'
INSERT INTO Dane(id, imie, nazwisko, pesel, dataurodzenia, plec)
    VALUES(2, 'Kasia', 'Ekola', '12345678901', '19500202','k')

-- zauwa¿amy, ¿e na kolumnie plec dzia³aj¹ zarówno wartoœæ domyœlna jak i regu³a 
SELECT * FROM Dane
