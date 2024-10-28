SELECT p.title, p.cost_rub, (SELECT AVG(_p.cost_rub) FROM projects AS _p)
FROM projects AS p
WHERE p.cost_rub > (SELECT AVG(_p.cost_rub) FROM projects AS _p);


