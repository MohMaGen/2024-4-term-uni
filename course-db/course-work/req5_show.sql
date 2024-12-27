SELECT
    c.full_name   AS "ФИО",
    cr.model      AS "Модель",
    o.cost        AS "Цена за день",
    o.issue_date  AS "Дата выдачи",
    o.return_date AS "Дата возврата"

FROM orders_of_client(
        (SELECT c.id
         FROM clients as c
         WHERE c.full_name = 'Краснов Дмитрий Александрович')) as o

LEFT JOIN clients AS c  ON c.id = o.client_id
LEFT JOIN cars    AS cr ON cr.VIN = o.car_VIN;
