SELECT p.title, a.family_name as "author name", p.cost_rub
FROM projects as p, authors as a
WHERE a.author_id = p.author_id

UNION ALL

SELECT p.title, 'Нет Автора' as "author name", p.cost_rub
FROM projects as p
WHERE p.author_id IS NULL

ORDER BY 1;
