SELECT p.title, a.age, 'Наивысший' AS "age related"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND
      a.age = (SELECT MAX(_a.age) FROM authors as _a)

UNION

SELECT p.title, a.age, 'Низший' AS "age related"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND
      a.age = (SELECT MIN(_a.age) FROM authors as _a)

union 
SELECT p.title, a.age, '' AS "age related"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND
      a.age != (SELECT MIN(_a.age) FROM authors as _a)

ORDER BY 1 desc;
