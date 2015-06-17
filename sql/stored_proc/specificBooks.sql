use library;
go

CREATE PROC SpecificBooks
@FirstName nvarchar(15)=NULL,
@LastName nvarchar(25)=NULL,
@Theme nvarchar(30)=NULL,
@Category nvarchar(30)=NULL,
@SortedField int=1,
@SortDirection nvarchar(4)='ASC'
AS
IF @SortedField<1 OR @SortedField>5
	THROW 50001, 'Choose correct sorting column (1-5)', 1;
	
IF NOT( @SortDirection='asc' OR @SortDirection='desc')
	THROW 50001, 'Set correct sorting order (asc/desc)',1;
	 
DECLARE @exec_msg nvarchar(max)='SELECT Books.Name AS Book, FirstName, LastName, Themes.Name AS Theme, Categories.Name AS Category
FROM Books JOIN Authors ON Books.Id_Author=Authors.Id
JOIN Themes ON Books.Id_Themes=Themes.Id
JOIN Categories ON Books.Id_Category=Categories.Id
WHERE FirstName Like ''%'+ ISNULL(@FirstName, '%')
	+'%'' AND LastName LIKE ''%'+ISNULL(@Lastname, '%')
	+'%'' AND Themes.Name LIKE ''%'+ISNULL(@Theme, '%') 
	+'%'' AND Categories.Name LIKE ''%'+ISNULL(@Category, '%')
	+'%'' ORDER BY '+CAST(@SortedField AS nvarchar)+' '+ CAST(@SortDirection AS nvarchar);

EXEC (@exec_msg);
go

exec SpecificBooks 'Алекс', NULL, 'Програм', NULL, 5, 'ASC'


EXEC SpecificBooks @Firstname='Алексей', @LastName=NULL,
 @Theme='Программирование', @Category=NULL,@SortedField=1,@Direction='ASC'