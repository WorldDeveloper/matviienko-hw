use library;
go

--Trigger Books_returned
DECLARE @CardId int =15;
DECLARE @BookId int;

if object_id('tempdb..#tmp_returned') IS NOT NULL
	DROP TABLE #tmp_returned;

select * into #tmp_returned from returned;
Declare @NumberOfBooks int;
SELECT @BookId=Id_Book FROM S_Cards WHERE id=@CardID;
SELECT @NumberOfBooks=Quantity FROM Books WHERE Id=@BookId;
---------------------------------------------------------
	update s_cards set DateIn=NULl where id=@CardId
	update s_cards set DateIn=GetDate() where id=@CardId
---------------------------------------------------------

SELECT Name AS BookTitle, @NumberOfBooks AS PreviousQuantity, Quantity AS ActualQuantity FROM Books WHERE Id=@BookId;

SELECT * FROM Returned
EXCEPT
SELECT * FROM #tmp_returned;

SELECT * FROM S_Cards WHERE id=@CardId;
