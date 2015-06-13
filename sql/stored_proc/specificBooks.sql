use library;
go

ALTER PROC SpecificBooks
@FirstName nvarchar(15)=NULL,
@LastName nvarchar(25)=NULL,
@Theme nvarchar(30)=NULL,
@Category nvarchar(30)=NULL,
@SortedField int=1,
@Direction nvarchar(4)='ASC'
AS
SELECT Books.Name AS Book, FirstName, LastName, Themes.Name AS Theme, Categories.Name AS Category
FROM Books JOIN Authors ON Books.Id_Author=Authors.Id
JOIN Themes ON Books.Id_Themes=Themes.Id
JOIN Categories ON Books.Id_Category=Categories.Id
WHERE FirstName Like ISNULL(@FirstName, '%') AND LastName LIKE ISNULL(@Lastname, '%') 
	AND Themes.Name LIKE ISNULL(@Theme, '%') AND Categories.Name LIKE ISNULL(@Category, '%')

EXEC SpecificBooks @Firstname='Алексей', @LastName=NULL,
 @Theme='Программирование', @Category=NULL,@SortedField=1,@Direction='ASC'