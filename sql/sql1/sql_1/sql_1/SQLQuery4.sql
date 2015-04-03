-- 4. Показать на экран названия и цены товаров с категорией "Кондитерские изделия", но только не торговой марки "Roshen".

SELECT Name, Price 
FROM Food 
WHERE Producer!='Roshen'