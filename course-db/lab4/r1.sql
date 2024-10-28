SELECT
    p.title as "Title",
    t.type_name as "Type",
    p.cost_rub as "Cost",
    AVG(p.cost_rub) OVER( PARTITION BY p.project_type_id )
       AS "Avg"
FROM projects AS p
LEFT JOIN project_types AS t
    ON t.project_type_id = p.project_type_id;

