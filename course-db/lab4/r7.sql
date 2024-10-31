SELECT	
    p.title AS "Title",
    p.project_type_id AS "Type ID",
    p.cost_rub AS "Cost"
FROM projects AS p
WHERE
    p.cost_rub * 2 >= (SELECT SUM(_p.cost_rub) 
                        FROM projects AS _p
                        WHERE  _p.project_type_id = p.project_type_id);
