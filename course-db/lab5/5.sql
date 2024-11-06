SELECT p.title, p.cost_rub, p.start_date
FROM projects AS p
WHERE p.cost_rub > (SELECT AVG(_p.cost_rub) FROM projects AS _p)

EXCEPT

SELECT p.title, p.cost_rub, p.start_date
FROM projects AS p
WHERE EXTRACT(YEAR FROM p.start_date) > 2020;


