#set text(font: "Noto Sans Georgian")

#set align(horizon + center)
#text(size: 24pt)[
    ЭЛЕКТРОТЕХНИКА И ЭЛЕКТРОНИКА\
    *Рабочая тетрадь*\
]

#text(size: 14pt)[
    Преподователь: Навроцкая Л.В.\
    Факультет: ЦиТХИН\
    Студент: Мохов М.Г.\
    Группа: КС-34 Вариант 11\
    Зачёт: #underline("          ")\
    «#underline("   ")» #underline("            ") 2024г.\
] 

#align(bottom)[
    Москва, 2024
]

#set align(left + top)
#set text(size: 11pt)
#set heading(numbering: "1")
#show figure.where(kind: image): set figure(supplement: "рис.")
#show figure.where(kind: table): set figure(supplement: "табл.")


#show heading:  it => {
    if it.level == 1 {
        pagebreak()
        align(center, text(size: 12.5pt, "Лабораторно-практическое занятие №" + counter(heading).display()))
        align(center, text(size: 16pt, upper(it.body)))
    }
	else if it.level == 2 {
        align(center, text(size: 14pt, it.body))	
    }
    else if it.level == 3 {
        align(center, text(size: 12.5pt, it.body))	
    }
}

#include "./lab1/report.typ"
#include "./lab2/report.typ"
#include "./lab3/report.typ"
#include "./lab4/report.typ"
