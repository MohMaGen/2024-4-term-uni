#import "@preview/codly:1.0.0": *

#let template(
        author-first-name: "Имя Отчество",
        author-last-name: "Фамилия",
        author-initials: "И.О.",
        group: "КС-34",
        variant: "NO",

        title: "Длинное-длинное название диссертации из достаточно большого количества сложных и непонятных слов",
        city: "Город",
        year: datetime.today().year(),
        organization: [Федеральное государственное автономное образовательное учреждение высшего образования "Длинное название образовательного учреждения \ "АББРЕВИАТУРА"],
        in-organization: "учреждении с длинным длинным длинным длинным названием, в котором выполнялась данная диссертационная работа", // в предложном падеже 
        organization-short: "Сокращенное название организации",
        supervisor-first-name: "Имя Отчество",
        supervisor-last-name: "Фамилия",
        supervisor-initials: "И.О.",
        supervisor-regalia: "уч. степень, уч. звание",
        supervisor-regalia-short: "уч. ст., уч. зв.",
        font-type: "Times New Roman",
        font-size: 14pt,
        link-color: blue.darken(60%),
        languages: (), 
        body,
) = {
    let author-name = author-last-name+" "+author-first-name
    let author-short = author-last-name+" "+author-initials
    let supervisor-name = supervisor-last-name+" "+supervisor-first-name
    let supervisor-short = supervisor-last-name+" "+supervisor-initials 

    set document(author: author-name, title: title)


    set text(
        font: font-type,
        lang: "ru",
        size: font-size,
        fallback: true,
        hyphenate: false,
        )

    // Установка свойств страницы 
    set page( margin: (top:2cm, bottom:2cm, left:2.5cm, right:1cm), )

    // форматирование заголовков
    set heading(numbering: "1.", outlined: true, supplement: [Раздел])
    show heading: it => {
        set align(center)
        let h-font-size = font-size
        let content = it


        if it.level == 1 {
            pagebreak()
            counter(figure).update(0)
            counter(math.equation).update(0)
            content = upper(content)
            h-font-size = 24pt
        } else if it.level == 2 {
            h-font-size = 18pt
        } else {
            h-font-size = 16pt
        }

        set text( font: font-type, size: h-font-size,)
        set block(above:3em,below:3em)
        content
    }

    // Настройка блоков кода
    show: codly-init.with()

    show link: set text(fill: link-color)

    // Нумерация уравнений 
    let eq_number(it) = {
        let part_number = counter(heading.where(level:1)).get()
            part_number

            it
    }
    set math.equation(numbering: num =>
        ("("+(counter(heading.where(level:1)).get() + (num,)).map(str).join(".")+")"),
        supplement: [Уравнение],
        )

    show figure: align.with(center)
    set figure(supplement: [Рисунок])
    set figure.caption(separator: [ -- ])
    set figure(numbering: num =>
      ((counter(heading.where(level:1)).get() + (num,)).map(str).join(".")),)

    show figure.where(kind:table): set figure.caption(position: top)
    show figure.where(kind:table): set figure(supplement: [Таблица])
    show figure.where(kind:table): set figure(numbering: num =>
        ((counter(heading.where(level:1)).get() + (num,)).map(str).join(".")),
        )
    show figure: set block(breakable: true)

    set enum(indent: 2.5em)

    show figure.where(kind:"listing"): set figure.caption(position: top)
    show figure.where(kind:"listing"): set figure(supplement: [Листинг])
    show figure.where(kind:table): set figure(numbering: num =>
        (num,).map(str).join("."),
        )

    state("section").update("body")



    {
        set text(size:16pt)
        set par(leading: 1em, justify: false)
        set align(center)
        organization
        line(length:100%)
        in-organization

        align(horizon, {
            v(1em)
            author-name
            " "
            group
            v(1em)
            [*#title*] // Название работы
            v(1em)
            [* #upper("Вариант №"+str(variant)) *]
        })

        set text(size:14pt)
        align(bottom, {
            set align(right)
            "Научный руководитель:"
            supervisor-regalia
            v(0em)
            supervisor-name
            v(0em)
            align(center)[#city -- #year]
        })
    }
    set align(left)
    set par(
            justify: true,
            linebreaks: "optimized",
            first-line-indent: 2.5em,
            leading: 1em,
           )


    set text(font-size)
    set page(
            numbering: "1",
            number-align:center+bottom,
            )
    show page: set text(12pt)

    outline(title: "Содержание", indent: 1.5em, depth: 3,)

    body
}
