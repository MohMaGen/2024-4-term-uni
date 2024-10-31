SELECT 
    p.title AS "Title",
    p.cost_rub AS "Cost",
    p.project_type_id AS "Type Id",
    (SELECT AVG(p3.cost_rub) 
        FROM projects AS p3 
        WHERE p3.project_type_id = p.project_type_id) AS "Type Avg"
FROM projects AS p
WHERE p.cost_rub > (SELECT AVG(p2.cost_rub) 
                    FROM projects AS p2 
                    WHERE p2.project_type_id = p.project_type_id);
