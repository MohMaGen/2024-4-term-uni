DROP VIEW Itog_query;

CREATE VIEW Itog_query AS SELECT 
	p.project_id AS project_id,
    p.author_id AS author_id,
	p.project_type_id AS project_type_id,
    p.start_date AS "Дата начала проекта",
    p.title AS "Название проекта",
    p.duration_years AS "Длительность прокта, лет.",
    p.cost_rub AS "Стоимость, тыс.руб."
FROM projects AS p;

SELECT * FROM Itog_query;
