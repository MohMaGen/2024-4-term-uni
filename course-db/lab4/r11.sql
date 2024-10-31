SELECT t.project_type_id, t.type_name
FROM project_types AS t
WHERE 1 IN (SELECT p.author_id
            FROM projects as p
            WHERE p.project_type_id = t.project_type_id);
