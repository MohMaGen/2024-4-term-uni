#import "lab.typ":template
#import "@preview/cetz:0.2.2"
#import "@preview/tablex:0.0.8": tablex, rowspanx, colspanx
#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#show figure.where(kind: "Add"): set figure(numbering:"1")

#show: template.with(
        author-first-name: "Марк Геннадьевич",
        author-last-name: "Мохов",
        author-initials: "М.Г.",
        group: "КС-34",
        variant: "11",

        title: [
            Лабораторная работа №8 по предмету управление данными:\
            "Работа с БД в СУБД MongoDB."
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

        font-type: "Noto Serif Georgian",
        link-color: blue.darken(60%),
        languages: (),
)

= Цель работы и практическое задание
== Цель.
Овладеть практическими навыками работы с CRUD-операциями, с
    вложенными объектами в коллекции базы данных MongoDB, агрегации и изменения
    данных, со ссылками и индексами в базе данных MongoDB.

== Практическое задание.
=== CRUD операции.
+ Сформируйте запросы для вывода списков каких либо объетов
    коллекции вашей БД. Ограничьте список. Отсортируйте списки по имени.

+ Ограничьте этот список с помощью функций ``` findOne``` и ``` limit```.

+  Модифицируйте запрос 1. для вывода списков объектов, исключив из
    результата какую-либо информацию и поле.


+ Вывести список объектов в коллекции в обратном порядке добавления.

+ Вывести список объектов коллекции вашей БД и использованием
    логических операторов, исключив вывод идентификатора.

+ Вывести список упорядоченный список имен объектов с информацией из
    коллекции вашей БД.

+  Создайте новую коллекцию (например, person) для часто встречающихся названий объектов в исходной коллекции, указав в качестве идентификатора кратко название объекта, далее включив полное название и описание. 

+ Включите в документы исходной коллекции ссылку на документы новой коллекции(например, person), использую второй способ автоматического связывания.

= Выполнение

== Сформируйте запросы для вывода списков каких либо объетов коллекции вашей БД. Ограничьте список. Отсортируйте списки по имени.

Вывести проекты типа _Технология_.
```js
db.projects_single.find({ proj_type: 'Технология' })
```

Чтобы ограеичеть использовал функцию ``` limit```, чтобы отсортировать по
    имени проектов --- функцию ``` sort({ project_name: 1 })```.

В результате получился запрос:

```js
db.projects_single.find({ proj_type: 'Технология' })
                  .limit(3).sort({ project_name: 1 })
```

Результат выполнения запроса:
```js
[
  {
    _id: ObjectId('6758258a4000176ef9e9496a'),
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'Технология',
    duration: 5,
    cost: 1200
  },
  {
    _id: ObjectId('675826254000176ef9e9496c'),
    start_date: ISODate('2005-02-02T00:00:00.000Z'),
    project_name: 'Проект3',
    family_name: 'Сидорова',
    age: 41,
    proj_type: 'Технология',
    duration: 3,
    cost: 950
  },
  {
    _id: ObjectId('6758275c4000176ef9e9496f'),
    start_date: ISODate('2005-04-04T00:00:00.000Z'),
    project_name: 'Проект6',
    family_name: 'Петрова',
    age: 29,
    proj_type: 'Технология',
    duration: 4,
    cost: 1100
  }
]
```

== Ограничьте этот список с помощью функций ``` findOne``` и ``` limit```.
Только один документ типа _Технология_ с помощью ``` findOne```.

```js
db.projects_single.findOne({ proj_type: 'Технология' })
```

Результат:
```js
{
  _id: ObjectId('6758258a4000176ef9e9496a'),
  start_date: ISODate('2004-03-02T00:00:00.000Z'),
  project_name: 'Проект1',
  family_name: 'Иванов',
  age: 30,
  proj_type: 'Технология',
  duration: 5,
  cost: 1200
}
```

Только один документ типа _Технология_ с помощью ``` limit```.
```js
db.projects_single.find({ proj_type: 'Технология' }).limit(1)
```

Результат:
```js
[
    {
      _id: ObjectId('6758258a4000176ef9e9496a'),
      start_date: ISODate('2004-03-02T00:00:00.000Z'),
      project_name: 'Проект1',
      family_name: 'Иванов',
      age: 30,
      proj_type: 'Технология',
      duration: 5,
      cost: 1200
    }
]
```

== Модифицируйте запрос 1. для вывода списков объектов, исключив из результата какую-либо информацию и поле.

Вывести 3 проекта, отсортированных по названию, типпа _Технология_ без индекса
и без информации об авторе проекта.

```js
db.projects_single.find({ proj_type: 'Технология' },
                        { _id: 0, age: 0, family_name: 0})
	              .limit(3).sort({ project_name: 1 })
```

Результат выполнения:
```js
[
  {
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    proj_type: 'Технология',
    duration: 5,
    cost: 1200
  },
  {
    start_date: ISODate('2005-02-02T00:00:00.000Z'),
    project_name: 'Проект3',
    proj_type: 'Технология',
    duration: 3,
    cost: 950
  },
  {
    start_date: ISODate('2005-04-04T00:00:00.000Z'),
    project_name: 'Проект6',
    proj_type: 'Технология',
    duration: 4,
    cost: 1100
  }
]
```

==  Вывести список объектов в коллекции в обратном порядке добавления.
Список проктов в обратном порядке добавления:

```js
db.projects_single.find().sort({ $natural: -1 })
```

Результат
```js
[
  {
    _id: ObjectId('675826254000176ef9e9496c'),
    start_date: ISODate('2005-02-02T00:00:00.000Z'),
    project_name: 'Проект3',
    family_name: 'Сидорова',
    age: 41,
    proj_type: 'Технология',
    duration: 3,
    cost: 950
  },
  {
    _id: ObjectId('6758275c4000176ef9e9496f'),
    start_date: ISODate('2005-04-04T00:00:00.000Z'),
    project_name: 'Проект6',
    family_name: 'Петрова',
    age: 29,
    proj_type: 'Технология',
    duration: 4,
    cost: 1100
  },
  {
    _id: ObjectId('6758272b4000176ef9e9496e'),
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект5',
    family_name: 'Сидорова',
    age: 41,
    proj_type: 'ОКР',
    duration: 3,
    cost: 900
  },
  {
    _id: ObjectId('675825e44000176ef9e9496b'),
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект2',
    family_name: 'Петрова',
    age: 30,
    proj_type: 'НИР',
    duration: 4,
    cost: 800
  },
  {
    _id: ObjectId('6758265d4000176ef9e9496d'),
    start_date: ISODate('2005-02-03T00:00:00.000Z'),
    project_name: 'Проект4',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'НИР',
    duration: 5,
    cost: 1000
  },
  {
    _id: ObjectId('6758258a4000176ef9e9496a'),
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'Технология',
    duration: 5,
    cost: 1200
  }
]
```

== Вывести список объектов коллекции вашей БД и использованием логических операторов, исключив вывод идентификатора.

```js
db.projects_single.find({ age: { $gte : 30 } }, { _id: 0 })
                  .sort({ name: 1 }) 
```
Результат 

```js
[
  {
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'Технология',
    duration: 5,
    cost: 1200
  },
  {
    start_date: ISODate('2005-02-03T00:00:00.000Z'),
    project_name: 'Проект4',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'НИР',
    duration: 5,
    cost: 1000
  },
  {
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект2',
    family_name: 'Петрова',
    age: 30,
    proj_type: 'НИР',
    duration: 4,
    cost: 800
  },
  {
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект5',
    family_name: 'Сидорова',
    age: 41,
    proj_type: 'ОКР',
    duration: 3,
    cost: 900
  },
  {
    start_date: ISODate('2005-02-02T00:00:00.000Z'),
    project_name: 'Проект3',
    family_name: 'Сидорова',
    age: 41,
    proj_type: 'Технология',
    duration: 3,
    cost: 950
  }
]
```


== Вывести список упорядоченный список имен объектов с информацией из коллекции вашей БД.

Упорядоченный список имн

```js
db.projects_single
  .find({}, { project_name: 1, cost: 1, duration: 1, _id: 0 })
  .sort({ project_name : 1 })
```

Результат
```js
[
  { project_name: 'Проект1', duration: 5, cost: 1200 },
  { project_name: 'Проект2', duration: 4, cost: 800 },
  { project_name: 'Проект3', duration: 3, cost: 950 },
  { project_name: 'Проект4', duration: 5, cost: 1000 },
  { project_name: 'Проект5', duration: 3, cost: 900 },
  { project_name: 'Проект6', duration: 4, cost: 1100 }
]
```

==  Сформировать курсор для вывода списка каких-либо объектов вашего варианта и вывести этот список

Первые два проекта по возрастанию названия.

```js
let cursor = db.projects_single.find();
cursor.sort({ project_name: 1 }).limit(2)
```

Результат
```js
[
  {
    _id: ObjectId('6758258a4000176ef9e9496a'),
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    family_name: 'Иванов',
    age: 30,
    proj_type: 'Технология',
    duration: 5,
    cost: 1200
  },
  {
    _id: ObjectId('675825e44000176ef9e9496b'),
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект2',
    family_name: 'Петрова',
    age: 30,
    proj_type: 'НИР',
    duration: 4,
    cost: 800
  }
]
```
== Вывести количество объектов вашей БД при определенном условии.
Количество проектов, авторам которых есть 30 лет.
```js
db.projects_single.find({ age: { $gte: 30 }}).count()
```

Результат:
```
5
```


== Сформировать запрос на подсчет количества документов с разными именами name для коллеции вашей БД (Использование метода ``` aggregate```).

Количество проектов определённого типа.

```js
db.projects_single.aggregate({ "$group": {
                                 _id: "$proj_type",
                                 count: { $sum: 1 }
                             }});
```

Результат:
```js
[
  { _id: 'Технология', count: 3 },
  { _id: 'НИР', count: 2 },
  { _id: 'ОКР', count: 1 }
]
```

==  Создайте новую коллекцию (например, person) для часто встречающихся названий объектов в исходной коллекции, указав в качестве идентификатора кратко название объекта, далее включив полное название и описание. 

Создание колекции авторов проектов:
```js
db.authors.insertMany([
        { _id: "I", family_name: "Иванов", age: 30 },
        { _id: "P", family_name: "Петрова", age: 29 },
        { _id: "S", family_name: "Сидорова", age: 41 }
    ])
```
Результат:
```
{ acknowledged: true, insertedIds: { '0': 'I', '1': 'P', '2': 'S' } }
```

Содержание коллекции ``` authors```:
```js
db.authors.find()
```

Результат:
```js
[
  { _id: 'I', family_name: 'Иванов', age: 30 },
  { _id: 'P', family_name: 'Петрова', age: 29 },
  { _id: 'S', family_name: 'Сидорова', age: 41 }
]
```
== Включите в документы исходной коллекции ссылку на документы новой коллекции(например, person), использую второй способ автоматического связывания.

Я создал копию коллекции ``` projects_single``` на всякий случай.
```js
db.projects_single.find().forEach(it => db.projects.insertOne(it));
```

Чтобы не изменять в ручную я использовал следующий запрос:
```js
db.projects.find().forEach((it) => {
    let id = db.authors.findOne({ family_name: it.family_name })._id; 

    db.projects.updateOne({ _id: it._id }, {
        $set: { "author": { $ref: "authors", $id: id } },
        $unset: { "family_name": 0, "age": 0 } });
    })
```

Этот запрос автоматически добавляет поле ``` author``` с ID автора, а
также удаляет уже не нужные поля ``` family_name```, ``` age```. 

В резульате содержание коллекции ``` projects``` выглядит следующим образом: 
```js
[
  {
    _id: ObjectId('6758258a4000176ef9e9496a'),
    start_date: ISODate('2004-03-02T00:00:00.000Z'),
    project_name: 'Проект1',
    proj_type: 'Технология',
    duration: 5,
    cost: 1200,
    author: DBRef('authors', 'I')
  },
  {
    _id: ObjectId('6758265d4000176ef9e9496d'),
    start_date: ISODate('2005-02-03T00:00:00.000Z'),
    project_name: 'Проект4',
    proj_type: 'НИР',
    duration: 5,
    cost: 1000,
    author: DBRef('authors', 'I')
  },
  {
    _id: ObjectId('675825e44000176ef9e9496b'),
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект2',
    proj_type: 'НИР',
    duration: 4,
    cost: 800,
    author: DBRef('authors', 'P')
  },
  {
    _id: ObjectId('6758272b4000176ef9e9496e'),
    start_date: ISODate('1970-01-01T00:00:00.000Z'),
    project_name: 'Проект5',
    proj_type: 'ОКР',
    duration: 3,
    cost: 900,
    author: DBRef('authors', 'S')
  },
  {
    _id: ObjectId('6758275c4000176ef9e9496f'),
    start_date: ISODate('2005-04-04T00:00:00.000Z'),
    project_name: 'Проект6',
    proj_type: 'Технология',
    duration: 4,
    cost: 1100,
    author: DBRef('authors', 'P')
  },
  {
    _id: ObjectId('675826254000176ef9e9496c'),
    start_date: ISODate('2005-02-02T00:00:00.000Z'),
    project_name: 'Проект3',
    proj_type: 'Технология',
    duration: 3,
    cost: 950,
    author: DBRef('authors', 'S')
  }
]
```

= Вывод

В резульатате выполнения лабораторной работы я овладел навыками практической 
работы с CRUD-операциями, с  вложенными объектами в коллекции базы данных
MongoDB, агрегации и изменения данных, со ссылками и индексами в базе данных 
MongoDB.
