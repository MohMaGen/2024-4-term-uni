SELECT 
    EXTRACT(YEAR FROM p.start_date) AS year,
    AVG(p.cost_rub) AS avg_cost
FROM projects AS p
GROUP BY year
HAVING AVG(p.cost_rub) >= (SELECT AVG(p.cost_rub) FROM projects AS p)
ORDER BY year;
