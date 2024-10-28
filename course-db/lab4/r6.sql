SELECT 
    p.title, a.family_name, a.age,
    (SELECT AVG(_a.age) FROM authors AS _a)
FROM projects as p, authors as a
WHERE
    a.age >= (SELECT AVG(_a.age) FROM authors AS _a) AND
    a.author_id = p.author_id;
