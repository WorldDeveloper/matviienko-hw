use library;
GO

CREATE PROC StudentsWithoutBooks
AS
SELECT COUNT(*) AS [Number of students never taking books from library]
FROM Students LEFT JOIN S_Cards 
ON Students.Id=S_Cards.Id_Student 
WHERE DateOut IS NULL;
GO

EXEC StudentsWithoutBooks;