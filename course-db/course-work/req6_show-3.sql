SELECT c.VIN AS "VIN", c.model AS "Модель"
FROM cars_of_client_at_moment(
        (SELECT c.id FROM clients as c
         WHERE c.full_name = 'Краснов Дмитрий Александрович'),
        '2022-11-02') as c;
