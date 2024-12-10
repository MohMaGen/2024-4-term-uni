#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx, vlinex, hlinex
#import "../common.typ": transpose, push_first, clear_csv


= РЕЗОНАНСЫ В ЦЕПИ СИНУСОИДАЛЬНОГО ТОКА
== Цель
    - Собрать цепь для наблюдения резонанса напряжения.
    - Расчитать параметры цепи, в которой наблюдается резонанс напряжения.
    - Собрать цепь для наблюдения резонанса токов.
    - Расчитать параметры цепи, в которой надлюдается резонанс токов.


== Ход решения.

=== №1 резонанс напряжения.
+ Цепь.
    #figure(
        caption: "Цепь для наблюдения резонанса напряжения.",
        image("./circuit1.png")
    )

+ Экперементальные значения.
    #figure(
        caption: "Таблица эксперементальных значений.",
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
    Значения были расчитаны по формулам:
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

+ Графики эксперементальных данных.
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
            caption: [Графики сопративлений. $R(C), ["Ом"]$, $X_L (C), ["Ом"]$, $X_C (C), ["Ом"]$],
            image("./plot1-3.png")
        )
        figure(
            caption: [Графики сопративлений. $R(C), ["Ом"]$, $Z (C), ["Ом"]$],
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
#pagebreak()
=== №2 резонанс токов.
+ Цепь.
    #figure(
        caption: "Цепь для наблюдения резонанса токов.",
        image("./circuit2.png")
    )

+ Экперементальные значения.
    #figure(
        caption: "Таблица эксперементальных значений.",
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
            $C, ["мкФ"]$, $I, ["А"]$, $I_R dot.c 10^3, ["A"]$, $I_L, ["А"]$,
            $I_C, ["А"]$,
            $Y dot.c 10^3, ["См"]$, $G dot.c 10^, ["См"]$,
            $B dot.c 10^3, ["См"]$, $S, ["Вт"]$, $P, ["Вт"]$,
             $cos phi dot.c 10^3$,
            vlinex(),
            ..clear_csv(csv("./output2.csv")).flatten(),
        )
    )

== Вывод
