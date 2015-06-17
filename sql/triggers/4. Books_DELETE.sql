use library;
go

ALTER TRIGGER Books_DELETE ON BOOKS
AFTER DELETE
AS
	INSERT INTO LibDeleted (Name, Pages, YearPress, Id_Themes, Id_Category, Id_Author, Id_Press, Comment, Quantity) 
	SELECT Name, Pages, YearPress, Id_Themes, Id_Category, Id_Author, Id_Press, Comment, Quantity FROM Deleted;

go

--delete from Books where id=23;
