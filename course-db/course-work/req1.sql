SELECT
    o.id AS "ID", 
    o.cost AS "Стм. за день.",
    o.issue_date AS "Дата выдачи",
    o.return_date AS "Дата возврата",
    s.name AS "Компания поставщик",
    c.model AS "Модель машины",
    cl.full_name AS "ФИО клента"
FROM orders AS o
LEFT JOIN suppliers AS s  ON s.id  = o.supplier_id
LEFT JOIN cars      AS c  ON c.VIN = o.car_VIN
LEFT JOIN clients   AS cl ON cl.id = o.client_id;
