USE [library]
GO


CREATE TRIGGER T_Cards_INSERT_ISTEAD ON T_Cards
INSTEAD OF INSERT
AS
BEGIN
	SET NOCOUNT ON;

	DECLARE @RowCount int=0;
	SELECT @RowCount=COUNT(*) from inserted;
	IF @RowCount>1
		BEGIN
			ROLLBACK TRAN;
			THROW 50000, 'Transaction was canceled. Limit INSERT to a single row', 1;
		END
	
	/*1. ... Сделать так, чтобы нельзя было выдать книгу, которой уже нет в библиотеке (по количеству).*/
	IF EXISTS(SELECT * FROM Books JOIN Inserted ON Books.Id=Inserted.Id_Book WHERE Quantity=0)
	BEGIN
		
		/* 	7. Если нет книги, которую хочет взять преподаватель, выдать ему одну случайную книгу.
		 В случае, если книги в библиотеке совсем закончились - выдать сообщение. */
		IF EXISTS(SELECT * FROM Books WHERE Quantity>0)	
		BEGIN
			INSERT T_Cards(Id_Teacher, Id_Book, DateOut, DateIn, Id_Lib)
				SELECT Id_Teacher, (SELECT TOP 1 Id FROM Books WHERE Quantity>0), GETDATE(), NULL, Id_Lib FROM Inserted
		END
		ELSE
			THROW 50000, 'Books are absent', 1;
	END
	ELSE
		INSERT T_Cards(Id_Teacher, Id_Book, DateOut, DateIn, Id_Lib)
			SELECT Id_Teacher, Id_Book, DateOut, DateIn, Id_Lib FROM inserted
	
	SET NOCOUNT OFF;
END;
go
