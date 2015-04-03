-- 3. Получить информацию о том, каких товаров сегодня или вчера доставили более 10 штук (getdate, dateadd, datediff).

SELECT * 
FROM Food 
WHERE (Date_of_delivery=CONVERT(date, GETDATE())
	OR Date_of_delivery=CONVERT(date, DATEADD(day, -1, GETDATE())))
	AND Quantity>10
