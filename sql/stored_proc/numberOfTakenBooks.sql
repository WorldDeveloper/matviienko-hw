use library;
GO

CREATE PROC NumberOfTakenBooks
AS
SELECT Groups.Name AS [Group/Department], COUNT(*) AS [Number of  taken books]
FROM Groups JOIN Students ON Students.Id_Group=Groups.Id
 JOIN S_Cards ON Students.Id=S_Cards.Id_Student 
GROUP BY Groups.Name
UNION
SELECT Departments.Name, COUNT(*) AS [Number of  taken books]
FROM Departments JOIN Teachers ON Teachers.Id_Dep=Departments.Id
 JOIN T_Cards ON Teachers.Id=T_Cards.ID_Teacher 
GROUP BY Departments.Name;

GO

EXEC NumberOfTakenBooks;