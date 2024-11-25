#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx
#import "../common.typ": transpose, push_first


= Реактивные элементы цепи синусоидального тока

== Цели.
+ Расчитать и построить зависимость сопротивления катушки и конденсатора от частоты питания.
+ Снять эксперементально и построить зависимость реактивного сопротивления катушки от частоты источника питания.
+ Сравнить рассчитанные и полученные результаты.
+ Записать вывод по результатам.

== Ход решения.
+ Цепь.
    #block(height: 20%, columns(2)[
        #figure(
            caption: "Схема с катушкой.",
            image("./circuit1.png")
        )
        #figure(
            caption: "Схема с конденсатором.",
            image("./circuit2.png")
        )
    ])

+ Рассчётные и экперементальные значения.
    #figure(
        kind: table,
        caption: "Результаты вычисления расчётных и эксперементальных значений.",
        tablex(
            columns: push_first(range(10).map(v => 1.2cm), (1cm, 1.1cm, 2cm)).flatten(),
            rows: range(9).map(v => 1.1cm),
            align: center + horizon,

            map-cells: cell => {
                if cell.y == 0 or cell.x < 3{ 
                    cell.content = {
                        set text(size: 11pt)
                        strong(cell.content)
                    }
                } else {
                    cell.content = {
                        set text(size: 9pt)
                        cell.content
                    }
                }
                cell
            },
            ..push_first(transpose(push_first(
                    csv("./data2.csv").map(v => v.map(m => float(m.trim()))),

                    ((rowspanx(4, rotate(-90deg, [Катушка])),[Расч], [$X_L, ["Ом"]$]),
                    (rowspanx(3, [Эксп]), [$U_L, ["В"]$]),
                    [$I_L, ["А"]$],
                    [$X_L = U_L / I_l, ["Ом"] $],

                    (rowspanx(4, rotate(-90deg, [Котденсатор])), [Расч], [$X_C, ["Ом"]$]),
                    (rowspanx(3, [Эксп]), [$U_C, ["В"]$]),
                    [$I_C, ["А"]$],
                    [$X_C = U_C / I_l, ["Ом"] $],
                ))),
                (colspanx(3, [Элементы и параметры цепи]),
                colspanx(10, [Частота, Гц]))
            ).flatten()
        ) 
    )

+ Графики
    #block(height: 27%, columns(2)[
        #figure(
            caption: "Графики расчётных данных",
            image("./plot1.png")
        )
        #figure(
            caption: "Графики эксперементальных данных",
            image("./plot2.png")
        )
    ])\

== Вывод
