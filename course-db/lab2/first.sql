DROP TABLE IF EXISTS authors;
DROP TABLE IF EXISTS projects;
DROP TABLE IF EXISTS project_types;


CREATE TABLE authors(
    author_id SERIAL PRIMARY KEY,
    family_name VARCHAR(50),
    age INT
);

CREATE TABLE project_types(
    project_type_id SERIAL PRIMARY KEY,
    type_name VARCHAR(50)
);

CREATE TABLE projects(
    project_id SERIAL PRIMARY KEY,
    title VARCHAR(50),
    start_date DATE,
    duration_years INT,
    cost_rub FLOAT,
    author_id INT,
    project_type_id INT,


    CONSTRAINT fk_author
        FOREIGN KEY(author_id)
            REFERENCES authors(author_id),
    CONSTRAINT fk_project_type
        FOREIGN KEY(project_type_id)
            REFERENCES project_types(project_type_id)
);

INSERT INTO authors(family_name, age)
VALUES('Иванов', 30),('Петрова', 29),('Сидорова', 41);

INSERT INTO project_types(type_name)
VALUES('Технология'),('НИР'),('ОКР');

INSERT INTO projects(title, start_date, duration_years, cost_rub, author_id, project_type_id)
VALUES  ('Проект1', '2004.02.03', 5, 1200,  1, 1),
        ('Проект2', '2005.01.15', 4, 800,   2, 2),
        ('Проект3', '2005.02.2',  3, 950,   3, 1),
        ('Проект4', '2005.03.2',  5, 1000,  1, 2),
        ('Проект5', '2005.02.14', 5, 900,   3, 3),
        ('Проект6', '2005.04.4',  5, 1100,  2, 1);
