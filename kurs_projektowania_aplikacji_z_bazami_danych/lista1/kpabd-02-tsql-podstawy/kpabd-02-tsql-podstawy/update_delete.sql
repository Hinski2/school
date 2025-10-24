USE Test;

--UPDATE

-- Aktualizujemy status ostatniego wypo¿yczenia ksi¹¿ki (niezale¿nie od egzemplarzy)
UPDATE Ksiazka SET Wypozyczona_Ostatni_Miesiac=1 FROM  Wypozyczenie w JOIN Egzemplarz e ON w.Egzemplarz_ID=e.Egzemplarz_ID JOIN Ksiazka k ON e.Ksiazka_ID=k.Ksiazka_ID WHERE w.Data>DATEADD(MONTH,-1, GETDATE());
go

-- Aktulizujemy datê ostatniego wypo¿yczenia jakiejkolwiek ksi¹¿ki
UPDATE Czytelnik SET Ostatnie_Wypozyczenie=Data FROM Wypozyczenie w JOIN Czytelnik e ON w.Czytelnik_ID=e.Czytelnik_ID AND w.Data = (SELECT MAX(w2.Data) FROM Wypozyczenie w2 WHERE w2.Czytelnik_ID = w.Czytelnik_ID)
go

select * from ksiazka
select * from czytelnik
select * from wypozyczenie order by czytelnik_id,data

--UPDATE Ksiazka SET Ostatnie_Wypozyczenie=Data FROM Wypozyczenie w JOIN Egzemplarz e ON w.Egzemplarz_ID=e.Egzemplarz_ID JOIN Ksiazka k ON e.Ksiazka_ID=k.Ksiazka_ID AND w.Data = (SELECT MIN(w2.Data) FROM Wypozyczenie w2, Ksiazka k2 WHERE w2.Egzemplarz_ID = w.Egzemplarz_ID and k2.Ksiazka_ID=k.Ksiazka_ID )


--DELETE

SELECT * FROM Czytelnik
GO

-- Usuwamy czytelnika, który w ostatnim okreœie (w zapytaniu 7 dni, normalnie w ci¹gu ostatnich np. 5 lat) nie wypo¿yczy³ ¿adnej ksi¹¿ki.
DELETE FROM Czytelnik FROM Wypozyczenie w JOIN Czytelnik e ON w.Czytelnik_ID=e.Czytelnik_ID AND w.Data = (SELECT MAX(w2.Data) FROM Wypozyczenie w2 WHERE w2.Czytelnik_ID = w.Czytelnik_ID) AND w.Data<DATEADD(DAY,-7, GETDATE())
GO
