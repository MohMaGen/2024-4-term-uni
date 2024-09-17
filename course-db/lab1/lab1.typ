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
            Лабораторная работа №1 по предмету управление данными:\
            "Основные понятия. Модели данных".
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
        supervisor-first-name: "Имя Отчество",
        supervisor-last-name: "Фамилия",
        supervisor-initials: "И.О.",
        supervisor-regalia: "уч. степень, уч. звание",
        supervisor-regalia-short: "уч. ст., уч. зв.",

        font-type: "Times New Roman",
        link-color: blue.darken(60%),
        languages: (),
)

= Задание
+ Разработать схему базы данных на основе следующих данных: [@table:variant]
#figure(
        kind: table,
        caption: "Профессорско-преподавательский состав (проекты)",

        tablex(
            columns: 7,
            header-rows: 1,
            align: center + horizon,
            auto-vlines: false,

            /* header */
            [Дата начала проекта], [Название проекта], [Фамилия], [Возраст],
            [Тип проекта], [Длительность проекта, лет], [Стоимость, тыс.руб],

            /* body */
            [3.02.04], [Проект1], [Иванов], [30], [Технология], [5], [1200],
            [15.01.05], [Проект2], [Петрова], [29], [НИР], [4], [800],
            [2.02.05], [Проект3], [Сидорова], [41], [Технология], [3], [950],
            [2.03.05], [Проект4], [Иванов], [30], [НИР], [5], [1000],
            [14.02.05], [Проект5], [Сидорова], [41], [ОКР], [3], [900],
            [4.04.05], [Проект6], [Петрова], [29], [Технология], [4], [1100],

        )
    )<table:variant>
+ В СУБД PostgreSQL создайте базу данных, содержащую не менее 3-х таблиц в 3-й
    нормальной форме.

+ Заполните таблицы данными.

= Решение

== Разработка схемы базы данных.
Из таблицы  @table:variant видно, что есть повторяющиеся поля: _Фамилия_, _Возраст_,
    _Тип проекта_. Причём _Фамилия_ и _Возраст_ связаны один к одному.

Таким образом можно выделить две таблицы: *Тип проекта* и *Автор*. В результате получиться
    база данных со следующей топологией. @pic:topology\
\
#figure(
    caption: [Схема базы данных.],
    {
    set text(size: 10pt)
    diagram(cell-size: 4mm,
        node((0, 0), tablex(columns: 2, align: center + horizon,
            colspanx(2, text(size: 12pt, [*Тип проекта*])),
            [ID Типа проекта], [INT],
            [Тип проекта], [VARCHAR(50)]
        )),
        node((1, 0), tablex(columns: 2, align: center + horizon,
            colspanx(2, text(size: 12pt, [*Автор*])),
            [ID Автора], [INT],
            [Фамилия], [VARCHAR(50)],
            [Возраст], [INT],
        )),
        node((0.5, 1), tablex(columns: 2, align: center + horizon,
            colspanx(2, text(size: 12pt, [*Проект*])),
            [ID Проекта], [INT],
            [Название], [VARCHAR(50)],
            [Дата начала проекта], [DATE],
            [Длительность проекта], [INT],
            [Стоимость], [INT],
            [ID Автора], [INT],
            [ID Типа проекта], [INT],
        ))
    )
    }
)<pic:topology>


== Установка и настройка PostgreSQL.
Установка отличается от предложенной, так как работа выполнялась на машине
    операционной системой Voidlinux. Первый шаг в установке postgresql на Voidlinux
    заключается в установке пакета postgresql и других вспомогательных пакетов.

```bash
doas xbps-install -Su postgresql postgresql-client postgresql-conttrlib
```

Во время установки будет создан пользователь *postgres*. Для этого пользователя
    требуется создать пароль.

```bash
doas passwd postgres
```

Далее требуется создать базу данных, для этого нужно сменить пользователя на *postgres*
    и запустить *psql*:

```bash
su postgres
psql -U postgres
```

Откроется shell взаимодействия с PostgreSQL, в нём нужно создать базу данных. Назовём
    её _first_lab_.

```sql
create database first_lab
```

== Создание таблиц
Опираясь на таблицу @table:variant напишем sql для создания таблиц. Для таблицы авторов получится
    следующий код:
```sql
CREATE TABLE authors(
    author_id SERIAL PRIMARY KEY,
    family_name VARCHAR(50) NOT NULL,
    age INT NOT NULL
);
```

Для таблицы типов проектов:
```sql
CREATE TABLE project_types(
    project_type_id SERIAL PRIMARY KEY,
    type_name VARCHAR(50) NOT NULL
);
```

Для таблицы проектов.
```sql
CREATE TABLE projects(
    project_id SERIAL PRIMARY KEY,
    title VARCHAR(50) NOT NULL,
    start_date DATE NOT NULL,
    duration_years INT NOT NULL,
    cost_rub FLOAT NOT NULL,
    author_id INT,
    project_type_id INT,
    CONSTRAINT fk_author
        FOREIGN KEY(author_id)
            REFERENCES authors(author_id),
    CONSTRAINT fk_project_type
        FOREIGN KEY(project_type_id)
            REFERENCES project_types(project_type_id)
);
```
== Заполнение таблицы
Заполним таблицу при помощи ```sql INSERT INTO``` данными в соответствии с таблицей
    @table:variant.
```sql
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
```

= Вывод
В процессе выполнения работы я изучил методы создания таблиц 3-й формы, и основные использования
    типов в sql.
Также при создании таблиц использовались ограничения для столбцов(```sql CONSTRAINT```).

