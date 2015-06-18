use library;
go

/*
написать триггер, который запретит вставку книги с годом издательства меньше 2010.
помимо однострочной вставки (insert values) учесть возможность многострочной вставки (insert select).
реализовать два сценария:
1) если в таблице вставляемых книг есть хотя бы одна "старая" книга, то вставка полностью отменяется (rollback tran).
2) если в таблице вставляемых книг есть хотя бы одна "новая" книга, то она должна попасть в Books, а все старые - нет.
*/

CREATE TRIGGER Books_INSERT_INSTEADOF ON Books
INSTEAD OF INSERT AS
BEGIN
	INSERT Books 
	SELECT Inserted.Name, Pages, YearPress, Id_Themes, Id_Category, Id_Author, Id_Press, Comment, Quantity 
	FROM Inserted 
	WHERE NOT EXISTS (
		SELECT * FROM Books 
		WHERE Books.Name=Inserted.Name AND 
				Books.Pages=Inserted.Pages AND 
				Books.YearPress=Inserted.YearPress AND 
				Books.Id_Author=Inserted.Id_Author AND
				Books.Id_Press=Inserted.Id_press
				);
		PRINT (CONCAT(@@rowcount,' books were added'));
END
go



