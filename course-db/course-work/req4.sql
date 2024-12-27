CREATE OR REPLACE VIEW ordered_cars_by_monthes AS
SELECT
    EXTRACT(YEAR FROM o.issue_date) AS year,
    EXTRACT(MONTH FROM o.issue_date) AS month,
    COUNT(*) as "count"
FROM orders as o
GROUP BY year, month

UNION

SELECT 
    EXTRACT(YEAR FROM v::date) AS year,
    EXTRACT(MONTH FROM v::date) AS month,
    0 as "count"
FROM generate_series(
        (SELECT MIN(_o.issue_date) FROM orders AS _o)::date,
        (SELECT MAX(_o.issue_date) FROM orders AS _o)::date,
        '1 month'::interval) v
WHERE NOT (EXTRACT(YEAR FROM v::date), EXTRACT(MONTH FROM v::date)) IN
        (SELECT
            EXTRACT(YEAR FROM __o.issue_date) AS _year,
            EXTRACT(MONTH FROM __o.issue_date) AS _month
        FROM orders as __o
        GROUP BY _year, _month)

ORDER BY year, month;
