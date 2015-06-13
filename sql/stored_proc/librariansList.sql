use library;
go

CREATE PROCEDURE LibrariansList
AS
SELECT Id, FirstName, Lastname, (SELECT COUNT(*) FROM S_Cards WHERE Id_Lib=Libs.Id)+
(SELECT COUNT(*) FROM T_Cards WHERE Id_lib=Libs.Id) As [Number]
FROM Libs;
Go

EXEC LibrariansList;