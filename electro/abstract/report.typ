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

#set text(    font: font-name,
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
[Министерство  науки и высшего образования РФ\ ] + v(10pt) +
[Российский химико-технологический университет имени Д.И. Менделеева\ ]
    + v(10pt) + line(length: 100%) + 
[Факультет цифровых технологий и химического инжиниринга\ ] + v(10pt) +
[Кафедра процесов и аппаратов химической технологии]
		))
	})
	align(center + horizon, {

		block(text(size: 18pt, upper([Реферат на тему:])))
		block(text(size: 18pt, [«Операционные усилители и обратная связь.»]))

	})

	align(bottom, { 
		align(right, block(align(left, [
				Исполнитель: гр. КС-34\
				Ф.И.О. студента: Мохов М.Г.\
				Ф.И.О. руководителя: Навроцкая Л.В. \
			])))
		
		v(1.5cm)
		
		align(center, [Москва, 2024])
	})
}

#pagebreak()

#let fli = 2.5em

#set align(left)
#set par(
        justify: true,
        linebreaks: "optimized",
        first-line-indent: fli,
        leading: 1em,
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
        h-font-size = 16pt
        block-padding = 2em

    } else if it.level == 2 {
        h-font-size = 15pt

    } else {
        h-font-size = 14pt
    }

    set block(above:block-padding, below:block-padding)
    set text( font: font-name, size: h-font-size,)
    content
}

#outline(title: "Содержание", indent: 1.5em, depth: 3,)

#set text(lang: "ru")


#pagebreak()
= Введение


