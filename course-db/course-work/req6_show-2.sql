SELECT
    c.VIN AS "VIN",
    c.model AS "Модель"
FROM cars_of_client_by_range(
        (SELECT c.id
         FROM clients as c
         WHERE c.full_name = 'Краснов Дмитрий Александрович'),
		'2022-1-1', '2023-1-1') as c;
