SELECT
    c.VIN AS "VIN",
    c.model AS "Модель"
FROM cars_of_client(
        (SELECT c.id
         FROM clients as c
         WHERE c.full_name = 'Пятков Алексей Маркович')) as c;
