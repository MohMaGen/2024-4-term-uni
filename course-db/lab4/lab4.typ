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
            Лабораторная работа №3 по предмету управление данными:\
            "Функции групироваки и агрегирования данных".
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
Форма оформления отчета в текстовом редакторе WORD.
+ Сформулировать на русском языке (в виде текста) осмысленные запросы.
+ Для сформулированного запроса написать код на языке SQL.
+ Выполнить запросы в СУБД PostgreSQL, приложить результаты в виде картинки.

Задания на создание и выполнения запросов:
№ Тип запроса
#figure(
    kind: table,
    tablex(
        columns: (auto, auto),
        colspanx(2, [*Оконные функции*]),
        [1.], [Придумать запрос на применение агрегирующих оконных функций],
        [2.], [Придумать запрос на применение ранжирующих оконных функций.],
        colspanx(2, [*Объединение таблиц самих с собой*]),
        [3.], [Вывести пары атрибутов одной сущности при определенном условии.],
        [4.], [Тоже, что и в пункте 3 с устранением избыточности без оператора DISTINCT.],
        colspanx(2, [*Подзапросы*]),
        [5.], [Придумать однотабличный запрос, использующий подзапрос в условии отбора строк поле фразы WHERE.],
        [6.], [Придумать многотабличный запрос, использующий подзапрос в условии отбора строк поле фразы WHERE.],
        [7.], [Придумать запрос, использующий подзапрос с агрегатной функцией в условии отбора строк поле фразы WHERE.],
        [8.], [Придумать запрос на использование подзапросов, которые выдают много строк с помощью оператора IN],
        [9.], [Придумать запрос, использующий подзапрос в предложении HAVING],
        [10], [Придумать запрос, использующий подзапрос в предложении FROM.],
        colspanx(2, [*Соотнесенные подзапросы*]),        
        [11], [Придумать запрос на использование соотнесенного подзапроса, который выдает много строк с помощью оператора IN.],
        [12], [Придумать запрос на сравнение таблицы с собой],
    )
)

= Решение

== Запрос на применение агрегирующих оконных функций
Средняя стоимость проектов разделённых по типам.
SQL запрос:
```sql
SELECT
    p.title AS "Title",
    t.type_name AS "Type",
    p.cost_rub AS "Cost",
    AVG(p.cost_rub) OVER( PARTITION BY p.project_type_id ) AS "AVG"
FROM projects AS p
LEFT JOIN project_types AS t 
    ON t.project_type_id = p.project_type_id;
```
#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto, auto),
        ..csv("./1.csv").flatten(),
    )
)
#pagebreak()

== Запрос на применение ранжирующих оконных функций.
Проекты по возрастанию даты.
```sql
SELECT
    title,
    start_date,
    row_number() OVER date_grades
FROM projects
WINDOW date_grades AS (order by start_date)
```
#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto),
        ..csv("./2.csv").flatten(),
    )
)
#pagebreak()

== Пары атрибутов одной сущности при определенном условии.
Пары проектов с одинаковой продолжительностью.

```sql
SELECT
    p1.duration_years,
    p1.project_id as "id1", p1.title,
    p2.project_id as "id2", p2.title
FROM projects as p1, projects as p2
WHERE
    p1.duration_years = p2.duration_years AND
    p1.project_id != p2.project_id;
```

#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto, auto, auto),
        ..csv("./3.csv").flatten(),
    )
)

#pagebreak()
== Пары атрибутов одной сущности при определенном условии с устранением избыточности.

Пары проектов с одинаковой продолжительностью.

```sql
SELECT
    p1.duration_years,
    p1.project_id as "id1", p1.title,
    p2.project_id as "id2", p2.title
FROM projects as p1, projects as p2
WHERE
    p1.duration_years = p2.duration_years AND
    p1.project_id > p2.project_id;
```

#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto, auto, auto),
        ..csv("./4.csv").flatten(),
    )
)

== Однотабличный запрос, использующий подзапрос в условии отбора строк поле фразы WHERE.
Проекты дороже средней стоимости.
```sql
SELECT p.title, p.cost_rub, (SELECT AVG(_p.cost_rub) FROM projects AS _p)
FROM projects AS p
WHERE p.cost_rub > (SELECT AVG(_p.cost_rub) FROM projects AS _p);
```
#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto),
        ..csv("./5.csv").flatten(),
    )
)
#pagebreak()
== Многотабличный запрос, использующий подзапрос в условии отбора строк поле фразы WHERE.
Проекты, авторы которых  старше среднего возраста.
```sql
SELECT 
    p.title, a.family_name, a.age,
    (SELECT AVG(_a.age) FROM authors AS _a)
FROM projects as p, authors as a
WHERE
    a.age >= (SELECT AVG(_a.age) FROM authors AS _a) AND
    a.author_id = p.author_id;
```
#figure(
    kind: table,
    caption: "Результат.",
    tablex(
        align: center + horizon,
        auto-vlines: false,
        header-rows: 1,
        columns: (auto, auto, auto, auto),
        ..csv("./6.csv").flatten(),
    )
)
#pagebreak()
==


