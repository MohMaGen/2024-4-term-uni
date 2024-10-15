-- Суммарная стоимость проектов Сидоровой.
SELECT SUM(p.cost_rub)
FROM authors as a, projects as p
WHERE   p.author_id = a.author_id AND
        a.family_name = 'Сидорова';

-- Средняя стоимость проектов, по годам.
SELECT AVG(p.cost_rub) as "avg cost", EXTRACT(YEAR FROM p.start_date) as "year"
FROM projects as p
GROUP BY EXTRACT(YEAR FROM p.start_date);

SELECT p.project_type_id, AVG(p.cost_rub), AVG(p.duration_years)
FROM projects AS p
GROUP BY p.project_type_id;

SELECT
    AVG(p.cost_rub) as "avg cost",
    AVG(p.duration_years) as "avg duration",
    COUNT(*),
    EXTRACT(YEAR FROM p.start_date) as "year",
    a.family_name as "family name"
FROM projects AS p
LEFT JOIN authors AS a ON a.author_id = p.author_id
GROUP BY a.family_name, EXTRACT(YEAR FROM p.start_date);


SELECT
    EXTRACT(YEAR FROM p.start_date) as "year",
    AVG(p.cost_rub) as "avg cost",
    AVG(p.duration_years) as "avg duration",
    COUNT(*)
FROM projects AS p
GROUP BY EXTRACT(YEAR FROM p.start_date)
HAVING EXTRACT(YEAR FROM p.start_date) BETWEEN 2005 AND 2024;


SELECT
    p.duration_years as "duration",
    AVG(p.cost_rub) as "avg cost",
    COUNT(*)
FROM projects AS p
GROUP BY p.duration_years
HAVING p.duration_years > 3;

SELECT
    EXTRACT(YEAR FROM p.start_date) as "year",
    AVG(p.cost_rub) as "avg cost",
    AVG(p.duration_years) as "avg duration",
    COUNT(*)
FROM projects AS p
GROUP BY EXTRACT(YEAR FROM p.start_date)
HAVING AVG(p.cost_rub) > 800;


SELECT
    EXTRACT(YEAR FROM p.start_date) as "year",
    AVG(p.cost_rub) as "avg cost",
    AVG(p.duration_years) as "avg duration",
    AVG(a.age) as "avg age",
    COUNT(t.type_name) as "diff types count"
FROM projects AS p
LEFT JOIN authors AS a ON a.author_id = p.author_id
LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
GROUP BY EXTRACT(YEAR FROM p.start_date);


SELECT
    SUM(p.cost_rub) * 0.8 as "sum_cost",
    AVG(p.duration_years) as "avg duration",
    AVG(a.age) as "avg age",
    EXTRACT(YEAR FROM p.start_date) as "year"
FROM projects AS p
    LEFT JOIN authors AS a ON a.author_id = p.author_id
    LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
GROUP BY EXTRACT(YEAR FROM p.start_date)
ORDER BY EXTRACT(YEAR FROM p.start_date) ASC;


SELECT
    SUM(p.cost_rub) * 0.8 as "sum_cost",
    AVG(p.duration_years) as "avg duration",
    AVG(a.age) as "avg age",
    EXTRACT(YEAR FROM p.start_date) as "year"
FROM projects AS p
    LEFT JOIN authors AS a ON a.author_id = p.author_id
    LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
GROUP BY EXTRACT(YEAR FROM p.start_date)
ORDER BY sum_cost DESC;
