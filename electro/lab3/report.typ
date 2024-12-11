#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx, vlinex, hlinex
#import "../common.typ": transpose, push_first, clear_csv


= РЕЗОНАНСЫ В ЦЕПИ СИНУСОИДАЛЬНОГО ТОКА
== Цель
    - Собрать цепь для наблюдения резонанса напряжения.
    - Посчитать параметры цепи, в которой наблюдается резонанс напряжения.
    - Собрать цепь для наблюдения резонанса токов.
    - Посчитать параметры цепи, в которой наблюдается резонанс токов.


== Ход решения.

=== №1 резонанс напряжения.
+ Цепь.
    #figure(
        caption: "Цепь для наблюдения резонанса напряжения.",
        image("./circuit1.png")
    )

+ Экспериментальные значения.
    #figure(
        caption: "Таблица экспериментальных значений.",
        tablex(
            columns: range(5).map(it => 2cm), 
            header-rows: 1,
            auto-vlines: false,
            align: center + horizon,
            repeat-header: true,
            rows: (1cm, 0.5cm),

            vlinex(), (), (), (), (), vlinex(),
            $C, ["мкФ"]$, $I, ["А"]$, $U_R, ["В"]$, $U_L, ["В"]$, $U_C, ["В"]$,
            ..clear_csv(csv("./measured_data.csv")).flatten(),
        )
    )
	#block(height: 2cm)

+ Расчётные данные.
    Значения были посчитаны по формулам:
    $
        R   = U_R / I; space
        X_L = U_L / I; space 
        X_C = U_C / I; space
        X   = X_L - X_C; space
        Z   = U / I\
        P   = R * I^2; space
        Q   = X * I^2; space
        S   = U * I
        phi = arctan(X / R)
    $


    #figure(
        caption: "Таблица расчётных значений.",
        tablex(
            columns: range(14).map(it => 1.2cm), 
            header-rows: 1,
            align: center + horizon,
            repeat-header: true,
            rows: (1cm, 0.5cm),
            auto-vlines: false,
            map-cells: cell => {
                if cell.y == 0 { 
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
            vlinex(),
            $C$, $I$, $U_R$, $U_L$, $U_C$, $R$, $X_L$, $X_C$, $Z$, $X$, $P$, $Q$, $S$, $phi$,
            vlinex(),
            ..clear_csv(csv("./output.csv")).flatten(),
        )
    )

+ Графики экспериментальных данных.
    #block(height: 25%, columns(2, {
        figure(
            caption: [График Силы Тока. $I(C), ["А"]$],
            image("./plot1-1.png")
        )
        figure(
            caption: [График напряжений. $U_R (C), ["В"]$, $U_L (C), ["В"]$, $U_C (C), ["В"]$],
            image("./plot1-2.png")
        )
    }))

+ Графики расчётных данных.
    #columns(2, {
        figure(
            caption: [Графики сопротивлений. $R(C), ["Ом"]$, $X_L (C), ["Ом"]$, $X_C (C), ["Ом"]$],
            image("./plot1-3.png")
        )
        figure(
            caption: [Графики сопротивлений. $R(C), ["Ом"]$, $Z (C), ["Ом"]$],
            image("./plot1-4.png")
        )
    })

    #block(height: 50%, columns(2, {
        figure(
            caption: [Графики мощностей. $P(C), ["Вт"]$, $S (C), ["Вт"]$],
            image("./plot1-5.png")
        )
        figure(
            caption: [График мощности. $Q(C) ["Вт"]$],
            image("./plot1-6.png")
        )
    }))

+ Векторная диаграмма резонанса напряжений.
    #figure(
        caption: [Векторная диаграмма резонанса напряжений.],
        image("./plot1-7.png", width: 80%)
    )


#pagebreak()
=== №2 резонанс токов.
+ Цепь.
    #figure(
        caption: "Цепь для наблюдения резонанса токов.",
        image("./circuit2.png")
    )

+ Экспериментальные значения.
    #figure(
        caption: "Таблица экспериментальных значений.",
        tablex(
            columns: range(5).map(it => 2cm), 
            header-rows: 1,
            auto-vlines: false,
            align: center + horizon,
            repeat-header: true,
            rows: (1cm, 0.5cm),

            vlinex(), (), (), (), (), vlinex(),
            $C, ["мкФ"]$, $I, ["мА"]$, $I_R, ["A"]$,
            $I_L, ["A"]$, $I_C, ["A"]$,
            ..clear_csv(csv("./measured_data2.csv")).flatten(),
        )
    )

+ Расчётные данные.
    #figure(
        caption: "Таблица расчётных значений.",
        tablex(
            columns: range(11).map(it => 1.3cm), 
            header-rows: 1,
            align: center + horizon,
            repeat-header: true,
            rows: (1cm, 0.5cm),
            auto-vlines: false,
            map-cells: cell => {
                if cell.y == 0 { 
                    cell.content = {
                        set text(size: 9pt)
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
            vlinex(),
            $C, ["мкФ"]$, $I, ["А"]$, $I_R, ["A"]$, $I_L, ["А"]$,
            $I_C, ["А"]$,
            $Y, ["См"]$, $G, ["См"]$,
            $B, ["См"]$, $S, ["Вт"]$, $P, ["Вт"]$,
             $cos phi $,
            vlinex(),
            ..clear_csv(csv("./output2.csv"), digits: 3).flatten(),
        )
    )
    #block(height: 1%)
+ Графики
    #figure(
        caption: [График сил тока от ёмкости конденсатора.],
        image("./plot2-1.png", width: 80%)
    )
    #figure(
        caption: [График проводимостей от ёмкости конденсатора.],
        image("./plot2-2.png", width: 80%)
    )
    #figure(
        caption: [График $cos phi$ от ёмкости конденсатора.],
        image("./plot2-3.png", width: 80%)
    )
    #figure(
        caption: [Векторная диаграмма векторов токов в момент резонанса.],
        image("./plot2-4.png", width: 80%)
    )
#pagebreak()
== Вывод
В ходе лабораторной работы я подтвердил наличие резонансного
поведения в исследуемых электрических цепях путём
экспериментальных вычислений. Эксперимент проводился
как для последовательного, так и для параллельных 
соединений. Результаты эксперимента совпали с теоретическими
предположениями.

Эксперимент подтвердил, что резонанс в цепи возникает при
равенстве сопротивлений (или электро проводимостей) реактивных
элементов. Подобный эффект наблюдается и при последовательном,
и при параллельных подключениях. 
