-- 3. �������� ���������� � ���, ����� ������� ������� ��� ����� ��������� ����� 10 ���� (getdate, dateadd, datediff).

SELECT * 
FROM Food 
WHERE (Date_of_delivery=CONVERT(date, GETDATE())
	OR Date_of_delivery=CONVERT(date, DATEADD(day, -1, GETDATE())))
	AND Quantity>10
