SELECT p.title, a.age, 'Выше среднего' AS "AVG_RELATED"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND a.age > (SELECT AVG(_a.age) FROM authors as _a)

UNION

SELECT p.title, a.age, 'Ниже среднего' AS "AVG_RELATED"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND a.age <= (SELECT AVG(_a.age) FROM authors as _a)

ORDER BY 1;
