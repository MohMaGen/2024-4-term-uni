SELECT
    cs.VIN AS "VIN",
    cs.model AS "Модель",
    cs.state AS "Состояние"
FROM cars_state('2023-1-5') as cs;
