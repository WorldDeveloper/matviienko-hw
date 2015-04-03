-- 1. Показать на экран все товары, наявное количество которых не указано.

SELECT *
FROM Food
WHERE Quantity=0 OR Quantity is NULL