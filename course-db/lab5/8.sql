UPDATE Itog_query
SET author_id = 1
WHERE author_id IS NULL;

UPDATE Itog_query
SET project_type_id = 1
WHERE project_type_id IS NULL;

SELECT * FROM Itog_query;
