use library;
go

/*
�������� �������, ������� �������� ������� ����� � ����� ������������ ������ 2010.
������ ������������ ������� (insert values) ������ ����������� ������������� ������� (insert select).
����������� ��� ��������:
1) ���� � ������� ����������� ���� ���� ���� �� ���� "������" �����, �� ������� ��������� ���������� (rollback tran).
2) ���� � ������� ����������� ���� ���� ���� �� ���� "�����" �����, �� ��� ������ ������� � Books, � ��� ������ - ���.
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



