use library;
go

CREATE PROC factorial
@f int
AS

IF @f>0 
	BEGIN
		DECLARE @f2 int=@f-1;
		EXEC @f2=factorial @f2;
		RETURN @f*@f2;
	END
ELSE
	IF @f=0
		RETURN 1;
	ELSE
		BEGIN
			DECLARE @msg NVARCHAR(100) = N'Error: number('+CAST(@f AS NVARCHAR)+N') is invalid.';
			THROW 50001, @msg, 1; 
		END
RETURN
GO


DECLARE @result int;
DECLARE @number int=-1;
EXEC @result=factorial @number;
PRINT 'factorial('+CAST(@number AS nvarchar)+') = '+ CAST(@result AS nvarchar);

