use library;
go

EXEC sys.sp_addmessage
			 @msgnum   = 60001
			,@severity = 16
			,@msgtext  = N'Error: number(%d) is not valid.'
			,@lang = 'us_english'; 
GO

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
			DECLARE @msg NVARCHAR(2048) = FORMATMESSAGE(60001, @f); 
			THROW 60001, @msg, 1; 
		END
RETURN
GO


DECLARE @result int;
DECLARE @number int=-1;
EXEC @result=factorial @number;
PRINT 'factorial('+CAST(@number AS nvarchar)+') = '+ CAST(@result AS nvarchar);

