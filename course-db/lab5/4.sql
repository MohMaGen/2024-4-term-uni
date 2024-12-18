SELECT p.title, p.cost_rub, p.start_date
FROM projects AS p
WHERE p.cost_rub > 1000

INTERSECT

SELECT p.title, p.cost_rub, p.start_date
FROM projects AS p
WHERE EXTRACT(YEAR FROM p.start_date) > 2005;


