SELECT c.PESEL, c.Nazwisko
FROM Czytelnik c WHERE c.Czytelnik_ID IN (
    SELECT w.Czytelnik_ID FROM Wypozyczenie w WHERE w.Egzemplarz_ID IN (
        SELECT e.Egzemplarz_ID FROM Egzemplarz e WHERE e.Ksiazka_ID IN (
            SELECT k.Ksiazka_ID FROM Ksiazka k )
        )
    )

-- semi joint działą jak: czy istnieje dopasowanie, jeśli je znajdzie przestaje szukać dalej 