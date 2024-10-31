SELECT p.title, p.cost_rub
FROM projects AS p
WHERE p.author_id IN (SELECT a.author_id FROM authors AS a WHERE a.age >= 30);
