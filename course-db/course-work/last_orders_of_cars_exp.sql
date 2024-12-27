SELECT
    c.model AS "Модель", 
    o.issue_date AS "Дата выдачи",
    o.return_date AS "Дата выдачи",
    o.cost AS "Цена за день",
    o.cost * (o.return_date - o.issue_date) AS "Общая цена"
FROM last_orders_of_cars as o
LEFT JOIN cars AS c ON o.car_VIN = c.VIN;
