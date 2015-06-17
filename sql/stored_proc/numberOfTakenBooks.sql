use library;
GO

CREATE PROC NumberOfTakenBooks
AS
SELECT Groups.Name AS [Group/Department], COUNT(S_Cards.Id) AS [Number of  taken books]
FROM Groups LEFT JOIN Students ON Students.Id_Group=Groups.Id
 LEFT JOIN S_Cards ON Students.Id=S_Cards.Id_Student 
GROUP BY Groups.Name
UNION
SELECT Departments.Name, COUNT(T_Cards.Id) AS [Number of  taken books]
FROM Departments LEFT JOIN Teachers ON Teachers.Id_Dep=Departments.Id
 LEFT JOIN T_Cards ON Teachers.Id=T_Cards.ID_Teacher 
GROUP BY Departments.Name;

GO

EXEC NumberOfTakenBooks;