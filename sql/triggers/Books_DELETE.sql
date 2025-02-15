USE [library]
GO

/*4. Чтобы при удалении книги, данные о ней копировались в таблицу LibDeleted.*/

CREATE TRIGGER Books_DELETE ON Books
AFTER DELETE
AS
	INSERT INTO LibDeleted (Name, Pages, YearPress, Id_Themes, Id_Category, Id_Author, Id_Press, Comment, Quantity) 
	SELECT Name, Pages, YearPress, Id_Themes, Id_Category, Id_Author, Id_Press, Comment, Quantity FROM Deleted;
go
