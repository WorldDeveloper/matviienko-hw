-- 5. Показать на экран все товары на букву "К", категория которых содержит букву "E".

SELECT * 
FROM Food 
WHERE Name LIKE 'К%' AND Category LIKE '%Е%'