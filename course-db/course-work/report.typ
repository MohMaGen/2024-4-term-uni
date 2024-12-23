#import "@preview/codly:1.0.0": *
#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx

#let font-size = 12pt
#let font-name = "Noto Serif Georgian"

#let author-name = "Мохов Марк Геннадьевич" 
#let author-short = "Мохов М.Г."
#let supervisor-name = "Семёнов Генадий Николаевич"
#let supervisor-short = "Семёнов Г.Н."

#let title = "Прокат автомобилей внутренний учет."


#set document(author: author-name, title: title)

#let link-color = blue

#set text(
    font: font-name,
    lang: "ru",
    size: font-size,
    fallback: true,
    hyphenate: false,
    )

// Установка свойств страницы 
#set page( margin: (top:2cm, bottom:2cm, left:3cm, right:1.5cm), )

// форматирование заголовков

// Настройка блоков кода
#show: codly-init.with()

#show link: set text(fill: link-color)

// Нумерация уравнений 
#let eq_number(it) = {
    let part_number = counter(heading.where(level:1)).get()
        part_number

        it
}

#set math.equation(numbering: num =>
    ("("+(counter(heading.where(level:1)).get() + (num,)).map(str).join(".")+")"),
    supplement: [Уравнение],
    )

#show figure: align.with(center)
#set figure(supplement: [Рисунок])
#set figure.caption(separator: [ -- ])
#set figure(numbering: num =>
  ((counter(heading.where(level:1)).get() + (num,)).map(str).join(".")),)

#show figure.where(kind:table): set figure.caption(position: top)
#show figure.where(kind:table): set figure(supplement: [Таблица])
#show figure.where(kind:table): set figure(numbering: num =>
    ((counter(heading.where(level:1)).get() + (num,)).map(str).join(".")),
    )
#show figure: set block(breakable: true)

#set enum(indent: 2.5em)

#show figure.where(kind:"listing"): set figure.caption(position: top)
#show figure.where(kind:"listing"): set figure(supplement: [Листинг])
#show figure.where(kind:table): set figure(numbering: num =>
    (num,).map(str).join("."),
    )

#state("section").update("body")



// title page.
#{
	align(center, {
		block(text(size: 14pt, tracking: 2pt,
                     [Министерство высшего образования и науки РФ\ ] + v(10pt) +
                     [Российский химико-технологический университет имени Д.И. Менделеева]))

		v(1.5cm)

                block(text(size: 14pt, [Кафедра информационных компьютерных технологий]))
	})
	align(center + horizon, {

		block(text(size: 18pt, [Отчёт по курсовой работе по дисциплине «Базы данных» на тему:]))
		block(text(size: 18pt, [«Прокат автомобилей внутренний учет.»]))

	})

	align(bottom, { 
		align(right, block(align(left, [
				Исполнитель: гр. КС-34\
				Ф.И.О. студента: Мохов М.Г.\
				Ф.И.О. руководителя: #supervisor-short \
			])))
		
		v(1.5cm)
		
		align(center, [Москва, 2024])
	})
}




#align(center, block(inset: (x: 2cm, y: 0pt), text(size: 14pt,
upper("ТЕХНИЧЕСКОЕ ЗАДАНИЕ НА КУРСОВУЮ РАБОТУ ПО ДИСЦИПЛИНЕ «Базы данных»"))))

#v(1cm)

Студенту #author-name группы КС-34

#v(1cm)

Тема курсовой работы

_«Прокат автомобилей внутренний учет.»_

#v(1cm)

Этапы разработки работы
+ #line(start: (0pt, 0.8em), length: 100%)
+ #line(start: (0pt, 0.8em), length: 100%)
+ #line(start: (0pt, 0.8em), length: 100%)
+ #line(start: (0pt, 0.8em), length: 100%)
+ #line(start: (0pt, 0.8em), length: 100%)


#v(1cm)

#tablex(
	columns: (40%, 30%, 30%),

	[Основные разделы], [Удельный вес раздела работы], [Срок выполнения],
	[Этап 1], [], [],
	[Этап 2], [], [],
	[Этап 3], [], [],
	[Этап 4], [], [],
	[Этап 5], [], [],
)

#v(1cm)

#line(start: (0pt, 0.8em), length: 100%)
#line(start: (0pt, 0.8em), length: 100%)


Дата выдачи задания #box(line(start: (0pt, 0.9em), length: 3cm))
	20#box(line(start: (0pt, 0.9em), length: 0.2cm)) г.
	#box(line(start: (0pt, 0.9em), length: 1cm))

Дата сдачи работы #box(line(start: (0pt, 0.9em), length: 3.4cm))
	20#box(line(start: (0pt, 0.9em), length: 0.2cm)) г.
	#box(line(start: (0pt, 0.9em), length: 1cm))

Дата защиты #box(line(start: (0pt, 0.9em), length: 4.35cm))
	20#box(line(start: (0pt, 0.9em), length: 0.2cm)) г.
	#box(line(start: (0pt, 0.9em), length: 1cm))

Руководитель работы #box(line(start: (0pt, 0.9em), length: 5cm))


#set page(numbering: "1")
#counter(page).update(1)

#let fli = 2.5em

#set align(left)
#set par(
        justify: true,
        linebreaks: "optimized",
        first-line-indent: fli,
        leading: 1.25em,
       )

#set text(size: font-size)

#set heading(numbering: none, outlined: true, supplement: [Раздел])
#show heading: it => {
    set align(center)
    let h-font-size = font-size
    let content = it
	let block-padding = 1.5em


    if it.level == 1 {
        counter(figure.where(kind: image)).update(0)
        //counter(figure.where(kind: table)).update(0)
        counter(math.equation).update(0)
        content = upper(content)
        h-font-size = 24pt
        block-padding = 3em

    } else if it.level == 2 {
        h-font-size = 18pt

    } else {
        h-font-size = 16pt
    }

    set block(above:block-padding, below:block-padding)
    set text( font: font-name, size: h-font-size,)
    content
}

#outline(title: "Содержание", indent: 1.5em, depth: 3,)

#set text(lang: "ru")


#pagebreak()
= Введение


#h(fli) Базы данных активно применяются  в организациях самого разного вида и назначения (от ИТ организаций, до никак не связанных с информационными технологиями организаций для хранения бюрократии различного рода). Базы данных являются основным методом организации, хранения и управлении информации, а также автоматизации бизнес-процессов. Процесс разработки базы данных включает в себя анализ предметной области, проектирования структуры данных, реализации связи между ними, а также создание инструментов для из сборки.


Целью этой курсовой работы является создание базы данных для организации по прокаты автомобилей, а также описание процесса создания этой базы данных. По большей части в этой работе будет рассмотрен процесс создания базы данных для системы обработки заказов, которая позволит хранить историю заказов со всей необходимой информацией о заказах.


В процессе выполнения работы будет выполнено проектирование инфологической и даталогической моделей базы данных, реализация схемы базы в СУБД PostgreSQL, наполнение базы осмысленными данными, а также разработка SQL-запросов, триггеров и хранимых процедур. Результаты будут представлены в виде отчета, включающего графические и текстовые материалы.

Работа демонстрирует практическое применение знаний по проектированию баз данных и написанию SQL-запросов, а также способствует развитию навыков работы с современными инструментами для управления данными.




#set heading(numbering: "1.")
#counter(heading).update(0)

#pagebreak()
= Техническое задание

#h(fli) Тема --- Прокат автомобилей внутренний учет. В задании также были представлены ключевые слова, описывающие предметную область:

*Автомобиль*: идентификационный номер, марка, компания-поставщик, число 
    штук данного типа общее, в гараже, выдано в настоящее время, выдано всего, 
    выдано в среднем за месяц, общий пробег; модель, длительность, мощность, 
    год выпуска и производитель.  

*Клиенты*: ФИО, паспортные данные, адрес, телефон; заказы, взятые 
    автомобили сейчас и в прошлом: номер, дата выдачи, дата возвращения, общая 
    стоимость заказа.  


= Инфологическая модель

#h(fli) Из технического задания я выделил четыре основных сущностей: Заказ, клиент,
	автомобиль, компания поставщик (@info-model-img). Заказ является основной
	дочерней сущностей, так как клиент может иметь различные заказы, автомобиль
	может быть заказ много раз, также поставщики могут поставлять автомобили
	для разных заказов. Заказ имеет информацию о клиенте (*ID* клиента), об
	автомобиле (*VIN Номер* автомобиля), об компании поставщике (*ID* компании
	поставщика), также заказ имеет стоимость за день, дату выдачи
	и дату возвращения. 

Клиент --- родительская сущность, хранящая всю персональную информацию об
	клиенте такую, как ФИО, паспортные данные и номер телефона. В качестве
	ключа используется поле *ID*.

Автомобиль --- родительская сущность, описывающая конкретный автомобиль. 
	Сущность автомобиля хранит в себе информацию об пробеге автомобиля,
	*VIN номер* автомобиля, а также марку. Для идентификации используется поле
	*VIΝ номер* так, как он является уникальным для каждого автомобиля.

Компания поставщик --- родительская сущность, описывающая компанию поставляющую
	автомобили. В качестве ключа используется поле *ID*.

#figure(
    kind: image,
    caption: [Инфологическая модель базы данных проката автомобилей.],
    block(inset: 1cm, image("./КБД.png"))
    )<info-model-img>


= Даталогическая модель

#h(fli) Даталогическая модель составлялась в соответствии с инфологической моделью.
	Сущность "Orders" соответствуют сущности "Заказ" из инфологической
	модели. "Orders" имеют следующие атрибуты:

	+ ``` id``` --- идентификационное поле. Числовой тип.
	+ ``` car_VIN``` --- VIN номер автомобиля. Связь один ко многим. Поле 
		является массивом символов длиной 17, в соответствии с международным
		стандартом. 

	+ ``` issue_date``` --- дата выдачи заказа. Является значением типа
		``` Date``` (в ``` postgreSQL``` этот тип отвечает за хранение
		информации об дате и времени).

	+ ``` return_date``` --- дата возвращения заказа. Так же, как и
		``` issue_date```, значение является типа ``` Date```.

	+ ``` supplier_id``` --- ID компании поставщика. Связь один ко многим.
		Является численным типом ``` INT```.

	+ ``` client_id``` --- ID клиента. Связь один ко многим.
		Является численным типом ``` INT```.

Сущность "Clients" соответствуют сущности "Клиент" из инфологической
	модели. "Clients" имеют следующий атрибуты:

	+ ``` id``` --- идентификационное поле.

	+ ``` full_name``` --- ФИО клиента. Значение является строкой.

	+ ``` id_number``` --- Номер и серия паспорта.
	+ ``` id_issue_date``` --- Дата выдачи паспорта.
	+ ``` id_insitution``` --- Код подразделения паспорта.

	+ ``` address``` --- Адрес.
	+ ``` phone``` --- Номер телефона клиента.

Сущность "Cars" соответствует сущности "Машина" из инфологической модели.
	"Cars" имеет следующие атрибуты:

	+ ``` VIN``` --- VIN номер автомобиля.
	+ ``` model``` --- Название модели и марки автомобиля.
	+ ``` milage_km``` --- Пробег автомобиля в километрах.


Сущность "Suppliers" соответствует сущности "Компания Поставщик" из 
	инфологической модели. "Suppliers" имеет следующие атрибуты:

	+ ``` id``` --- идентификационное поле.
	+ ``` name``` --- Название компании.

== Схема БД

#figure(
	kind: image,
	caption: [Даталогическая модель.],
	image("./DLD_CW.png")
)

== SQL код для создания таблиц

#raw(read("./init.sql"), block: true, lang: "sql")

== Наполнение таблиц

#raw(read("./fill.sql"), block: true, lang: "sql")

== Таблицы

#figure(
    kind: table,
    caption: [Таблица клиентов.],
    tablex(
        header-rows: 1,
        align: horizon,
        columns: (auto, 3.5cm, auto, auto, auto, auto, auto),
        ..csv("./clients.csv").flatten()
    )
)

#figure(
    kind: table,
    caption: [Таблица машин.],
    tablex(
        header-rows: 1,
        align: horizon,
        columns: (auto, auto, auto),
        ..csv("./cars.csv").flatten()
    )
)

#figure(
    kind: table,
    caption: [Таблица компаний поставщиков.],
    tablex(
        header-rows: 1,
        align: horizon,
        columns: (auto, auto),
        ..csv("./suppliers.csv").flatten()
    )
)

#figure(
    kind: table,
    caption: [Таблица заказов.],
    tablex(
        header-rows: 1,
        align: horizon,
        columns: range(7).map(it => auto),
        ..csv("./orders.csv").flatten()
    )
)

#pagebreak()
= Результаты запросов

== Список всех заказов
#raw(read("./req1.sql"), block: true, lang: "sql")


#figure(
    kind: table,
    caption: [Результат выполнения запроса 1.],
    tablex(
        columns: (0.6cm, 1.3cm, 1.9cm, 1.9cm, 4.7cm, 2.5cm, 3.5cm),
        align: horizon,
        map-cells: cell => {
            cell.content = {
                set text(size: 10pt)
                cell.content
            }
            cell
        },

        ..csv("./res1.csv").flatten()
    )
)


= Выводы и заключение

= Список литературы
