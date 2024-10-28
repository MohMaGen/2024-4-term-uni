SELECT
    p1.duration_years,
    p1.project_id as "id1", p1.title,
    p2.project_id as "id2", p2.title
FROM projects as p1, projects as p2
WHERE
    p1.duration_years = p2.duration_years AND
    p1.project_id > p2.project_id;
