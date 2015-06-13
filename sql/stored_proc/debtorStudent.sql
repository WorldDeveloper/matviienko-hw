use library;
GO

CREATE PROC DebtorStudent
AS
SELECT FirstName, LastName, CAST(DateOut AS date) AS DateOut, Name AS Book
FROM Students JOIN S_Cards 
ON Students.Id=S_Cards.Id_Student 
JOIN Books ON S_Cards.Id_book=Books.Id
WHERE DateIn IS NULL
ORDER BY LastName;
GO

EXEC DebtorStudent;