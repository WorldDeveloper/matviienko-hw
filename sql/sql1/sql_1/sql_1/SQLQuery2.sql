--2. ��������� ��� ��������� ������� �� ���� � ������ (� ������ ������ �� ��� ������).


SELECT SUM(Price*Quantity*(100.0-Discount)/100.0) AS [Total receipts for milk and bread including discounts]
FROM Food
WHERE Category LIKE '%������%' OR Category LIKE '%���%'