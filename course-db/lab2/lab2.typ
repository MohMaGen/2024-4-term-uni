#import "lab.typ":template
#import "@preview/cetz:0.2.2"
#import "@preview/tablex:0.0.8": tablex, rowspanx, colspanx
#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge


#show: template.with(
        author-first-name: "Марк Геннадьевич",
        author-last-name: "Мохов",
        author-initials: "М.Г.",
        group: "КС-34",
        variant: "11",

        title: [
            Лабораторная работа №2 по предмету управление данными:\
            "Типы объединения SQL".
        ],
        city: "Москва",

        organization: [
        Министерство науки и высшего образования Российской Федерации\
        Российский химико-технологический университет имени Д. И. Менделеева
        ],
        in-organization: [
            Факультет цифровых технологий и химического инжиниринга\
            Кафедра информационных компьютерных технологий
        ],
        supervisor-first-name: "Генадий Николаевич",
        supervisor-last-name: "Семёнов",
        supervisor-initials: "Г.Н.",
        supervisor-regalia: "",
        supervisor-regalia-short: "уч. ст., уч. зв.",

        font-type: "Times New Roman",
        link-color: blue.darken(60%),
        languages: (),
)

= Задание
+ В созданной на Лаб.1 БД вставить 2 записи, которые не имеют значений некоторых
    внешних ключей, в дочернюю таблицу БД.
+ Сформулировать на русском языке (в виде текста) осмысленные запросы
    соответствующего типа (@tbl-xrs), затем написать код на языке SQL и вставить в
    отчет по Лаб.+
+ Выполнить запросы в СУБД PostgreSQL, вставить результаты в отчет в виде
    картинки.
+ Загрузить отчет (файл *.doc или *.pdf) и резервную копию БД в папку ЗАДАНИЕ
    «Сдать базу данных по Лабораторной работе №2» ТЕМЫ 3

#figure(
    kind: table,
    caption: "Задание.",
    tablex(
        columns: 2,
        header-rows: 1,
        align: center + horizon,
        [*№*], [*Тип запроса*],
        colspanx(2, [*Внутреннее объединение таблиц*]),
        [1.], [Соединение 2-х таблиц, с определенными полями, с одним условием],
        [2.], [Соединение 3-х таблиц с определенными полями, с двумя условиями.],
        [3.], [Соединение 3-х таблиц с определенными полями, с тремя условиями.],
        [4.], [Соединение 3-х таблиц, со всеми значащими полями, кроме Id],
        [5.], [Соединение 2-х таблиц, определенными полями, в диапазоне дат],
        colspanx(2, [*Левое внешнее объединение таблиц*]),
        [6.], [Соединение 2-х таблиц дочерней и родительской с определенными полями, так чтобы в результате запроса были значения null.],

        colspanx(2, [*Правое внешнее объединение таблиц*]),
        [7.], [Соединение 2-х таблиц дочерней и родительской с определенными полями, так чтобы в результате запроса были значения null.],
        colspanx(2, [*Внешнее полное объединение таблиц*]),
        [8.], [Соединение 3-х таблиц дочерней и родительских с определенными полями, так чтобы в результате запроса были значения null]
    )
)<tbl-xrs>

= Решение

== Вставить две записи. Для этого воспользоваться простым  ```sql INSERT``` запросом: 
Я решил вставить четыре поля: 2 без автора и 2 без типа проекта.
```sql
insert into projects(title, start_date, duration_years, cost_rub, author_id)
values  ('Проект Ы', '2024.02.03', 5, 1200, 1),
        ('Проект А', '2024.05.03', 3, 200, 2);

insert into projects(title, start_date, duration_years, cost_rub, project_type_id)
values  ('Проект Ы', '2026.02.03', 5, 1200, 1),
        ('Проект А', '2024.05.03', 3, 200, 2);
```

== Сформулируем осмысленные запросы в соответствии с (@tbl-xrs):
+ Вывести все названия проектов за авторством Иванова, если есть автор.
    ```sql
  SELECT
    authors.family_name, projects.title
  FROM
    authors, projects
  WHERE
    authors.author_id = projects.author_id AND
    authors.family_name = 'Иванов';
    ```
    результат @tlbl-res-1

+ Вывести названия проектов  за авторством Иванова типа Технология.
    ```sql
    SELECT
        authors.family_name, projects.title, project_types.type_name
    FROM
        authors, projects, project_types
    WHERE
        projects.author_id = authors.author_id AND
        projects.project_type_id = project_types.project_type_id AND
        project_types.type_name = 'Технология' AND
        authors.family_name = 'Иванов';
    ```
    результат @tlbl-res-2.

+ Вывести проекты типа НИР с продолжительностью больше 3 лет и с
    автором младше 30 лет:
    ```sql
    SELECT
        authors.family_name, projects.title, project_types.type_name
    FROM
        authors, projects, project_types
    WHERE
            projects.author_id = authors.author_id AND
            projects.project_type_id = project_types.project_type_id AND
            project_types.type_name = 'НИР' AND
            projects.duration_years > 3 AND
            authors.age <= 30;
    ```
    результат @tlbl-res-3.

+ Вывести все проекты со всей из информации:
    ```sql
    SELECT
        projects.title, projects.start_date, projects.duration_years, projects.cost_rub,
        authors.family_name, authors.age,
        project_types.type_name
    FROM
        authors, projects, project_types
    WHERE
        projects.author_id = authors.author_id AND
        projects.project_type_id = project_types.project_type_id;
    ```
    результат @tlbl-res-4.
    
+ Вывести Проекты и их авторов, которые начались в 2025 году:
    ```sql
    SELECT
        a.family_name, p.title, p.start_date
    FROM
        authors as a, projects as p
    WHERE
        a.author_id = p.author_id AND
        p.start_date BETWEEN '2005-01-01' and '2005-12-31';
    ```
    результат @tlbl-res-5.

+ Вывести названия проектов и даты их начала, а так же тип проекта, если он есть:
    ```sql
    SELECT
        p.title, p.start_date, t.type_name
    FROM projects AS p
    LEFT JOIN project_types AS t
    ON p.project_type_id = t.project_type_id;
    ```
    результат @tlbl-res-6.

+ Вывести названия проектов и даты их начала, а так же тип проекта, если он есть: 
    ```sql
    SELECT
        p.title, p.start_date, t.type_name
    FROM project_types AS t
    RIGHT JOIN projects AS p
    ON p.project_type_id = t.project_type_id;
    ```
    результат @tlbl-res-7.

+ Вывести всю информацию о проектах и об авторах с типами, если они есть.
    ```sql
    SELECT
        p.title, p.start_date, p.duration_years, p.cost_rub,
        a.family_name, a.age,
        t.type_name
    FROM
        projects AS p
    FULL JOIN authors AS a ON a.author_id = p.author_id
    FULL JOIN project_types AS t ON p.project_type_id = t.project_type_id
    ```
    результат @tlbl-res-8.

= Вывод
    В результате выполнения лабораторной работы, я научился создавать объединения баз данных разных типов.

= Таблицы
#figure(
    caption: "Результат 1",
    kind: table,
    tablex(
        columns: 2,
        header-rows: 1,
        [*family_name*], [*title*],
        [Иванов], [Проект1],
        [Иванов], [Проект4],
        [Иванов], [Проект Ы],
    )
)<tlbl-res-1>

#figure(
    caption: "Результат 2",
    kind: table,
    tablex(
        columns: 3,
        header-rows: 1,
        [*family_name*],[*title*],[*type_name*],
        [Иванов],[Проект1],[Технология],
    )
)<tlbl-res-2>

#figure(
    caption: "Результат 3",
    kind: table,

    tablex(
        columns: 3,
        header-rows: 1,
        [*family_name*],[*title*],[*type_name*],
        [Иванов],[Проект2],[НИР],
        [Сидорова],[Проект4],[НИР],
    )
)<tlbl-res-3>

#figure(
    caption: "Результат 4",
    kind: table,

    tablex(
        columns: 7,
        header-rows: 1,
        [*title*],[*start_date*],[*duration_years*],[*cost_rub*],[*family_name*],[*age*],[*type_name*],
        [Проект1],[2004-02-03],[5],[1200],[Иванов],[30],[Технология],
        [Проект2],[2005-01-15],[4],[800],[Петрова],[29],[НИР],
        [Проект3],[2005-02-02],[3],[950],[Сидорова],[41],[Технология],
        [Проект4],[2005-03-02],[5],[1000],[Иванов],[30],[НИР],
        [Проект5],[2005-02-14],[5],[900],[Сидорова],[41],[ОКР],
        [Проект6],[2005-04-04],[5],[1100],[Петрова],[29],[Технология],
    )
)<tlbl-res-4>

#figure(
    caption: "Результат 5",
    kind: table,

    tablex(
        columns: 3,
        header-rows: 1,
        [*family_name*],[*title*],[*start_date*],
        [Петрова],[Проект2],[2005-01-15],
        [Сидорова],[Проект3],[2005-02-02],
        [Иванов],[Проект4],[2005-03-02],
        [Сидорова],[Проект5],[2005-02-14],
        [Петрова],[Проект6],[2005-04-04],
    )
)<tlbl-res-5>

#pagebreak()
#figure(
    caption: "Результат 6",
    kind: table,
    tablex(
        columns: 3,
        header-rows: 1,
        [*title*],[*start_date*],[*type_name*],
        [Проект1],[2004-02-03],[Технология],
        [Проект2],[2005-01-15],[НИР],
        [Проект3],[2005-02-02],[Технология],
        [Проект4],[2005-03-02],[НИР],
        [Проект5],[2005-02-14],[ОКР],
        [Проект6],[2005-04-04],[Технология],
        [Проект Ы],[2024-02-03],[],
        [Проект А],[2024-05-03],[],
        [Проект Ы],[2026-02-03],[Технология],
        [Проект А],[2024-05-03],[НИР],
    )
)<tlbl-res-6>

#figure(
    caption: "Результат 7",
    kind: table,
    tablex(
        columns: 3,
        header-rows: 1,
        [*title*],[*start_date*],[*type_name*],
        [Проект1],[2004-02-03],[Технология],
        [Проект2],[2005-01-15],[НИР],
        [Проект3],[2005-02-02],[Технология],
        [Проект4],[2005-03-02],[НИР],
        [Проект5],[2005-02-14],[ОКР],
        [Проект6],[2005-04-04],[Технология],
        [Проект Ы],[2024-02-03],[],
        [Проект А],[2024-05-03],[],
        [Проект Ы],[2026-02-03],[Технология],
        [Проект А],[2024-05-03],[НИР],
    )
)<tlbl-res-7>

#figure(
    caption: "Результат 8",
    kind: table,

    tablex(
        columns: 7,
        header-rows: 1,

        [*title*],[*start_date*],[*duration_years*],[*cost_rub*],[*family_name*],[*age*],[*type_name*],
        [Проект1],[2004-02-03],[5],[1200],[Иванов],[30],[Технология],
        [Проект2],[2005-01-15],[4],[800],[Петрова],[29],[НИР],
        [Проект3],[2005-02-02],[3],[950],[Сидорова],[41],[Технология],
        [Проект4],[2005-03-02],[5],[1000],[Иванов],[30],[НИР],
        [Проект5],[2005-02-14],[5],[900],[Сидорова],[41],[ОКР],
        [Проект6],[2005-04-04],[5],[1100],[Петрова],[29],[Технология],
        [Проект Ы],[2024-02-03],[5],[1200],[Иванов],[30],[],
        [Проект А],[2024-05-03],[3],[200],[Петрова],[29],[],
        [Проект Ы],[2026-02-03],[5],[1200],[],[],[Технология],
        [Проект А],[2024-05-03],[3],[200],[],[],[НИР],
    )
)<tlbl-res-8>
