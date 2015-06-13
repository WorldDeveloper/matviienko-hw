use library;
go

CREATE PROC TSBooks
AS
SELECT Count(*) AS [Count] FROM S_Cards JOIN T_Cards
ON S_Cards.Id_Book=T_Cards.Id_Book;
go

EXEC TSBooks;