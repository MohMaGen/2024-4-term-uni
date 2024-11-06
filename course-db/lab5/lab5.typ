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
            Лабораторная работа №5 по предмету управление данными:\
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

Форма оформления отчета в текстовом редакторе WORD:
+ В отчете указать номер вашего варианта и приложить в виде скришотов: ERD-диаграмму БД и данные всех таблиц.
+ Сформулировать на русском языке (в виде текста) осмысленные запросы.
+ Для сформулированного запроса написать код на языке SQL.
+ Выполнить запросы в СУБД PostgreSQL, приложить результаты в виде картинки.

#figure(
    tablex(
        columns: (auto, auto),
        align: center + horizon,

        colspanx(2, [*Объединение, внешнее Объединение запросов*]),

        [1.], [Создайте объединение из двух запросов, которое показало бы имена ОБЪЕКТов, некоторый
        числовой параметр (значения NULL не показывать) их в дочерней таблице и текстовый
        параметр. Строки набора, которые имеют значения числового параметра больше среднего,
        должны иметь текстовый параметр "Выше среднего", а те которые имеют меньше среднего
        текстовый параметр "Ниже среднего". Результат отсортируйте по алфавиту имен.],
        [2.], [Создайте объединение из двух запросов, которое показало бы имена ОБЪЕКТов, некоторый
        числовой параметр в дочерней таблице (значения NULL не показывать) и текстовый параметр.
        Строки набора, которые имеют максимальное значение числового параметра, должны, кроме
        того, иметь текстовый параметр "Наивысший", а те которые имеют минимальное значение
        "Низший". Результат отсортируйте по алфавиту имен в обратном порядке.],
        [3.], [Создайте внешнее объединение двух запросов (смотрите методические рекомендации к
        лаб.№ 6).],

        colspanx(2,[*Пересечение запросов*]),

        [4.], [Создайте запрос на пересечение однотипных запросов c разными условиями отбора строк.],

        colspanx(2,[*Вычитание запросов*]),

        [5.], [Создайте запрос на вычитание однотипных запросов c разными условиями отбора строк.],

        colspanx(2,[*Представления*]),

        [6.], [Создайте модифицируемое представление (с опцией проверки), которое ограничивает
        доступ к определенным строкам и столбцам в родительской таблице.],
        [7.], [Создайте представление "Itog_query" для просмотра и модификации данных, в котором
        отражены данные исходной таблицы с наименованиями полей вашего варианта задания в Лаб.
        №1.],
        [8.], [С помощью созданного представления "Itog_query" произведите обновления в строке,
        содержащей NULL-значения.],
        [9.], [Создайте представление (с возможностью модификации и с опцией проверки) для дочерней
        таблицы.],
        [10.], [Создайте представление "Avg_Obj", которое бы показывало усредненные значения
        ОБЪЕКТов для каждого ОБЪЕКТа после его имени],
    )
)

= Решение

== Задание 1.
Проекты и возраст авторов соответствующих проектов.
```sql
SELECT p.title, a.age, 'Выше среднего' AS "AVG_RELATED"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND
      a.age > (SELECT AVG(_a.age) FROM authors as _a)

UNION

SELECT p.title, a.age, 'Ниже среднего' AS "AVG_RELATED"
FROM projects AS p, authors AS a
WHERE a.author_id = p.author_id AND
      a.age <= (SELECT AVG(_a.age) FROM authors as _a)

ORDER BY 1;
```
#figure(tablex(columns: (auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./1.csv").flatten()))

#pagebreak()
== Задание 2.
Проекты и возраст авторов соответствующих проектов.

```sql
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
```

#figure(tablex(columns: (auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./2.csv").flatten()))

#pagebreak()
== Задание 3.

#raw(read("./3.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./3.csv").flatten()))


#pagebreak()
== Задание 4.

#raw(read("./4.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./4.csv").flatten()))


#pagebreak()
== Задание 5.

#raw(read("./5.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./5.csv").flatten()))

#pagebreak()
== Задание 6.

#raw(read("./6.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto, auto), auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./6.csv").flatten()))

#pagebreak()
== Задание 7.

#raw(read("./7.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto, auto, auto, auto, auto), 
        auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./7.csv").flatten()))


#pagebreak()
== Задание 8.

#raw(read("./8.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto, auto, auto, auto, auto), 
        auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./8.csv").flatten()))

#pagebreak()
== Задание 9.

#raw(read("./9.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto), 
        auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./9.csv").flatten()))

#pagebreak()
== Задание 10.

#raw(read("./10.sql"), lang: "sql", block: true)
#figure(tablex(columns: (auto, auto, auto, auto, auto, auto, auto), 
        auto-vlines: false, header-rows:1,
        align: center + horizon, ..csv("./10.csv").flatten()))

