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
 
#figure(
    kind: table,
    caption: "Задания на создание и выполнения запросов:",
    tablex(
        columns: 2,
        header-rows: 1,
        align: center + horizon,
        [*№*], [*Тип запроса*],
        [1.], [Создать запрос на простейшее агрегирование с использованием какой-либо функции агрегирования.],
        [2.], [Создать запрос на агрегирование с группировкой по значению функции (например, на функцию выделения года из данных типа date)],
        [3.], [Создать запрос на группировку данных по одному полю с использованием функций группировки.],
        [4.], [Создать запрос на группировку данных по двум полям с использованием функций группировки. И объяснить в чем разница результатов по сравнению с п.3.],
        [5.], [Создать запрос на группировку данных по одному полю с использованием функций группировки и условием отбора (HAVING по датам).],
        [6.], [Создать запрос на группировку данных по одному полю с использованием функций группировки и условием отбора (HAVING) по числовому полю.],
        [7.], [Создать запрос на группировку данных по одному полю с использованием функций группировки и условием отбора (HAVING с групповой функцией) по числовому полю.],
        [8.], [Создать запрос на группировку данных по одному полю с использованием функций группировки с соединением 3-х таблиц.],
        [9.], [Создать вычисляемый запрос с соединением 3-х таблиц с сортировкой строк по возрастанию в вычисленном поле.],
        [10.], [Создать вычисляемый запрос с соединением 3-х таблиц, с группировкой по одному полю. Сортировку результирующего набора строк выполнить по убыванию в вычисленном поле.],
    )
)<tbl-xrs>

= Решение

== Сформулировать на русском языке (в виде текста) осмысленные запросы.
+ Суммарная стоимость всех проектов Сидоровой.
    ```sql
    SELECT SUM(p.cost_rub)
    FROM authors as a, projects as p
    WHERE   p.author_id = a.author_id AND
            a.family_name = 'Сидорова';
    ```
    #figure(
        caption: "Первое задание.",
        image("./first.png")
    )

+ Средняя стоимость проектов, по годам.
    ```sql
    SELECT AVG(p.cost_rub) as "avg cost", EXTRACT(YEAR FROM p.start_date) as "year"
    FROM projects as p
    GROUP BY EXTRACT(YEAR FROM p.start_date);
    ```
    #figure(
        caption: "Второе задание.",
        image("./second.png")
    )


+ Средняя стоимость и продолжительность проектов по типам проектов.
    ```sql
    SELECT p.project_type_id, AVG(p.cost_rub), AVG(p.duration_years)
    FROM projects AS p
    GROUP BY p.project_type_id;
    ```
    #figure(
        caption: "Третье задание.",
        image("./third.png")
    )

+ Данные о проектах сгруппированные по авторам и годам.
    ```sql
    SELECT
        AVG(p.cost_rub) as "avg cost",
        AVG(p.duration_years) as "avg duration",
        COUNT(*),
        EXTRACT(YEAR FROM p.start_date) as "year",
        a.family_name as "family name"
    FROM projects AS p
    LEFT JOIN authors AS a ON a.author_id = p.author_id
    GROUP BY a.family_name, EXTRACT(YEAR FROM p.start_date);
    ```
    #figure(
        caption: "Четвётрое задание.",
        image("./fourth.png")
    )

+ Данные о проектах сгруппированные по годам в диапозоне с 2004 по 2024.
    ```sql
    SELECT
        EXTRACT(YEAR FROM p.start_date) as "year",
        AVG(p.cost_rub) as "avg cost",
        AVG(p.duration_years) as "avg duration",
        COUNT(*)
    FROM projects AS p
    GROUP BY EXTRACT(YEAR FROM p.start_date)
    HAVING EXTRACT(YEAR FROM p.start_date) BETWEEN 2005 AND 2024;
    ```
    #figure(
        caption: "Пятое задание.",
        image("./fifth.png")
    )

+ Средняя стоимость проектов продолжительностью болье 3 лет.
    ```sql
    SELECT
        p.duration_years as "duration",
        AVG(p.cost_rub) as "avg cost",
        COUNT(*)
    FROM projects AS p
    GROUP BY p.duration_years
    HAVING p.duration_years > 3;
    ```
    #figure(
        caption: "Шестое задание.",
        image("./sixth.png")
    )

+ Данные о проектах сгруппированые по годам со средней стоимостью болье 800.
    ```sql
    SELECT
        EXTRACT(YEAR FROM p.start_date) as "year",
        AVG(p.cost_rub) as "avg cost",
        AVG(p.duration_years) as "avg duration",
        COUNT(*)
    FROM projects AS p
    GROUP BY EXTRACT(YEAR FROM p.start_date)
    HAVING AVG(p.cost_rub) > 800;
    ```
    #figure(
        caption: "Седьмое задание.",
        image("./seventh.png")
    )

+ Полные данные об проектах, авторах и типах сгруппированные по годам.
    ```sql
    SELECT
        EXTRACT(YEAR FROM p.start_date) as "year",
        AVG(p.cost_rub) as "avg cost",
        AVG(p.duration_years) as "avg duration",
        AVG(a.age) as "avg age",
        COUNT(t.type_name) as "diff types count"
    FROM projects AS p
    LEFT JOIN authors AS a ON a.author_id = p.author_id
    LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
    GROUP BY EXTRACT(YEAR FROM p.start_date);
    ```
    #figure(
        caption: "Восьмое задание.",
        image("./eighth.png")
    )

+ Полные данные об проектах, авторах и типах сгруппированные по годам в порядке возрастания названий.
    ```sql
    SELECT
        SUM(p.cost_rub) * 0.8 as "sum_cost",
        AVG(p.duration_years) as "avg duration",
        AVG(a.age) as "avg age",
        EXTRACT(YEAR FROM p.start_date) as "year",
        p.title
    FROM projects AS p
        LEFT JOIN authors AS a ON a.author_id = p.author_id
        LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
    GROUP BY EXTRACT(YEAR FROM p.start_date)
    ORDER BY p.title ASC;
    ```
    #figure(
        caption: "Девятое задание.",
        image("./ninth.png")
    )

+ Полные данные об проектах, авторах и типах сгруппированные по годам в порядке возрастания суммарной стоимости проектов.
    ```sql
    SELECT
        SUM(p.cost_rub) * 0.8 as "sum_cost",
        AVG(p.duration_years) as "avg duration",
        AVG(a.age) as "avg age",
        EXTRACT(YEAR FROM p.start_date) as "year",
        p.title
    FROM projects AS p
        LEFT JOIN authors AS a ON a.author_id = p.author_id
        LEFT JOIN project_types AS t ON t.project_type_id = p.project_type_id
    GROUP BY EXTRACT(YEAR FROM p.start_date)
    ORDER BY sum_cost DESC;
    ```
    #figure(
        caption: "Десятое задание.",
        image("./tenth.png")
    )


= Вывод
В результате выполнения лабораторной работы научился составлять запросы 
по группировке данных, использовать функции агрегирования и сортировать
результат.
