--2. Посчитать всю возможную выручку за хлеб и молоко (с учётом скидок на эти товары).


SELECT SUM(Price*Quantity*(100.0-Discount)/100.0) AS [Total receipts for milk and bread including discounts]
FROM Food
WHERE Category LIKE '%молоко%' OR Category LIKE '%хліб%'