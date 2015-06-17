use library;
go

--Trigger Books_returned from Teacher
CREATE PROC Test_Trigger_Cards_UPDATE_Date_In
 @CardId int,
 @Table nvarchar(50)
 AS
 
if object_id('tempdb..#tmp_returned') IS NOT NULL
	DROP TABLE #tmp_returned;

select * into #tmp_returned from returned;
DECLARE @exec_msg nvarchar(max);
DECLARE @BookId int;

SET @exec_msg='SELECT @BookId=Id_Book FROM '+@Table+' WHERE id='+CAST(@CardID AS nvarchar);
Print @BookId;
Print @Table;
Print @CardId;
EXEC sp_executesql @exec_msg, N'@BookId int out', @BookId out
Declare @NumberOfBooks int;
SELECT @NumberOfBooks=Quantity FROM Books WHERE Id=@BookId;
---------------------------------------------------------
	EXEC ('UPDATE '+@Table+' SET DateIn=NULl WHERE id='+@CardId);
	EXEC ('UPDATE '+@Table+' SET DateIn=GetDate() WHERE id='+@CardId);
---------------------------------------------------------

SELECT Name AS BookTitle, @NumberOfBooks AS PreviousQuantity, Quantity AS ActualQuantity FROM Books WHERE Id=@BookId;

SELECT * FROM Returned
EXCEPT
SELECT * FROM #tmp_returned;

EXEC('SELECT * FROM '+@Table+' WHERE id='+@CardId);
GO


-------------------------------------------------------------------------
--exec Test_Trigger_Cards_UPDATE_Date_Out @CardId=196, @Table='T_Cards'
--exec Test_Trigger_Cards_UPDATE_Date_Out @CardId=15, @Table='S_Cards'
