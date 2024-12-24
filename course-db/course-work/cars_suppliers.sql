SELECT
    c.VIN   AS "VIN",
    c.model AS "Модель",
    s.name  AS "Компания поставщик"
FROM cars AS c
LEFT JOIN suppliers AS s ON s.id = supplier_of_car(c.VIN);
