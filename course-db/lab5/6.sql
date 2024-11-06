CREATE VIEW View_By_Years
AS SELECT 
    EXTRACT(YEAR FROM start_date) as year, AVG(cost_rub) as "avg cost",
	SUM(cost_rub) as "sum cost", AVG(duration_years) as "avg duration"
FROM projects
GROUP BY year
ORDER BY year;

SELECT * FROM  View_By_Years;
