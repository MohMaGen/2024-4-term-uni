CREATE VIEW Avg_Obj AS SELECT
    p.title AS "Название",
    a.family_name AS "Автор",
    t.type_name AS "Тип",

    (SELECT AVG(_p.cost_rub)
            FROM projects AS _p 
            WHERE p.project_type_id = _p.project_type_id)
            AS "средняя стоимость проектов типа",
    (SELECT AVG(_p.cost_rub)
            FROM projects AS _p 
            WHERE p.author_id = _p.author_id)
            AS "Средняя стоимость проектов автора",

    (SELECT AVG(_p.duration_years)
            FROM projects AS _p 
            WHERE p.project_type_id = _p.project_type_id)
            AS "Средняя дл. проектов типа",

    (SELECT AVG(_p.duration_years)
            FROM projects AS _p 
            WHERE p.author_id = _p.author_id)
            AS "Средняя дл. проектов автора"

FROM projects AS p
LEFT JOIN authors AS a
    ON a.author_id = p.author_id
LEFT JOIN project_types AS t
    ON t.project_type_id = p.project_type_id

ORDER BY p.title;

