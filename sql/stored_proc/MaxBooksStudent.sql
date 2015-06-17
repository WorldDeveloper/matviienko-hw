USE Library;
go

CREATE PROC MaxBooksStudent
AS
SELECT TOP 1 WITH TIES FirstName, LastName FROM Students JOIN S_Cards ON Students.Id=S_Cards.Id_Student
GROUP BY FirstName, Lastname
ORDER BY Count(Students.Id) DESC;
go


exec MaxBooksStudent;