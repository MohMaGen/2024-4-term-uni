#import "./lab.typ": template
#import "@preview/cetz:0.3.0"
#import "@preview/tablex:0.0.8": tablex, rowspanx, colspanx
#import "@preview/fletcher:0.5.1" as fletcher: diagram, node, edge

#show: template.with(
        author-first-name: "Марк Геннадьевич",
        author-last-name: "Мохов",
        author-initials: "М.Г.",
        group: "КС-34",
        variant: "11",

        title: [САМОСТОЯТЕЛЬНАЯ РАБОТА\ по электротехнике.],
        city: "Москва",

        organization: [
        Министерство науки и высшего образования Российской Федерации\
        Российский химико-технологический университет имени Д. И. Менделеева
        ],
        in-organization: [
            Факультет цифровых технологий и химического инжиниринга\
            Кафедра процессов и аппаратов химической технологии
        ],
        supervisor-first-name: none,
        supervisor-last-name: none,
        supervisor-initials: none,
        supervisor-regalia: none,
        supervisor-regalia-short: none,

        font-type: "Times New Roman",
        link-color: blue.darken(60%),
        languages: (),
)

= Вариант
Мохов Марк Геннадьевич. М -- 13, Г -- 4 следовательно

#figure(
    caption: "параметры 11 варианта для РГР.",
    table(
        columns: (auto, auto),
        [*Параметр*], [*Значение*],
        [А], [3],
        [Б], [3],
        [В], [4],
    )
)

= Задание 1
== Условие

Выполнить указанные ниже задания для электрической схемы, изображенной на @drw-1_1, по данным таблицы @tbl-1_1
+ Начертить электрическую схему и записать исходные данные в соответствии с вариантом.
+ Записать систему уравнений по первому и второму законам Кирхгофа, необходимую для определения токов в ветвях системы.
+ Определить напряжения в узлах методом узловых напряжений, предварительно упростив схему (если это необходимо преобразовать схему к трем узлам).
+ Проверить правильность решения, применив первый закон Кирхгофа.
+ Составить уравнение баланса мощности и проверить его.
+ Построить в масштабе потенциальную диаграмму для внешнего контура.

#figure(
    kind: table,
    caption: "Задание",
    tablex(
        rows: auto,
        align: center,
        columns: (auto, auto, auto, auto, auto, auto, auto, auto, auto, auto),
        [№-рис.],[Е1, В],[Е2, В],[Е3, В],[R1,Ом],[R2,Ом],[R3,Ом],[R4,Ом],[R5,Ом],[R6 ,Ом],
        [1-А],[10+Б],[20+В],[40+А],[1 + Б],[2 + В],[3 + А],[4+Б+А],[5+Б+В],[6+В+А],
        [1-3],[13],[23],[43],[4],[6],[6],[10],[10],[11],
    )
)<tbl-1_1>

#figure(
    caption: "Рисунок 1-3.",
    cetz.canvas({
        import cetz.draw: *
        let v = 3
        let a = (-1.5*v, -v);
        let b = (1.5*v, -v);
        let o_1 = (0,v);
        rect(a, o_1)
        rect(o_1, b)
        let h = 0.8
        let w = 0.3
        set-style(fill: white)
        rect((-1.5*v - w, -h), (-1.5*v + w, h))
        rect((1.5*v - w, 0.2), (1.5*v + w, 0.2+1.5*h))
        rect((1.5*v - w, -0.2), (1.5*v + w, -0.2-1.5*h))
        circle((1.5*v, 0.2+1.5*h+0.7), radius: 0.5)
        circle((1.5*v, -0.2-1.5*h - 0.7), radius: 0.5)
        line()
    })
)<drw-1_1>
