#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx, vlinex, hlinex
#import "../common.typ": transpose, push_first, clear_csv
#import "@preview/cetz:0.3.1"

= ТРЕХФАЗНЫЕ ЦЕПИ

== Цель работы:
+ Изучить схемы соединения трехфазных цепей.

+ Экспериментально определить соотношения между фазными и линейными 
    напряжениями и токами.

+ Построить векторные диаграммы напряжений и токов для симметричных 
    режимов.

== Ход работы:
 

#let star = "«Звезда»"

=== Соединение #star:


+ Цепь.
    #figure( caption: [Цепь #star.], image("./circuit1.png") )


+  Расчётные и эксперементальные данные:
    #figure(
        kind: table,
        caption: [Таблица значений цепи #star. ],
        tablex(
            map-cells: cell => {
                if cell.y < 2 or cell.x < 2 { 
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
            columns: push_first(range(15).map(it => auto),
                                (1.1cm, 1.5cm)).flatten(),
            rows: (1cm, 1.6cm, auto,),
            align: horizon + center,

            colspanx(2, rowspanx(2, "Режим цепи")),
            colspanx(11, "Измерить"), colspanx(4, "Рассчитать"),
            $U_A$, $U_B$, $U_C$, $U_n$, $U_(A B)$, $U_(A C)$, $U_(B C)$,
            $I_A$, $I_B$, $I_C$, $I_n$,
            $P_A$, $P_B$, $P_C$, $P_"ц"$,
            ..transpose(
                push_first(transpose(clear_csv(csv("./result1-1.csv"))),
                    (
                        (rowspanx(2, [с нейт. пров.]), [симм.]),
                        ([несимм.]),
                        (rowspanx(2, [без нейт. пров.]), [симм.]),
                        ([несимм.]),
                    )
                )
            ).flatten()
        )
    )   

+ Векторные диаграммы:
    #let s = 3;

    #columns(2, {
    align(center, figure(
        kind: image,
        caption: [Векторная диаграмма симметричной цепи #star с нейтральным проводом.],

        cetz.canvas({
        import cetz.draw: *

        set-style(content: (frame: "rect", stroke: none, fill: none, padding: 0.3))
        set-style(mark: (end: "straight"))
        line((0,-s), (0,s), name: "OY")
        line((s,0), (-s,0), name: "OX")
        content("OY.end", text(size: 12pt, $+1$), anchor: "west")
        content("OX.end", text(size: 12pt, $+j$), anchor: "south")

    	let r_i = 0.5*s;
        line((0,0), (angle:  90deg, radius: r_i), stroke: green, name: "I_A")
        line((0,0), (angle: 330deg, radius: r_i), stroke: blue,  name: "I_B")
        line((0,0), (angle: 210deg, radius: r_i), stroke: red,   name: "I_C")

        content("I_A.end", text(size: 12pt, $arrow(I_A)$), anchor: "north-west")
        content("I_B.end", text(size: 12pt, $arrow(I_B)$), anchor: "east")
        content("I_C.end", text(size: 12pt, $arrow(I_C)$), anchor: "west")

    	let r_u = 0.7*s;
        line((0,0), (angle:  90deg, radius: r_u), stroke: green, name: "U_A")
        line((0,0), (angle: 330deg, radius: r_u), stroke: blue,  name: "U_B")
        line((0,0), (angle: 210deg, radius: r_u), stroke: red,   name: "U_C")

        content("U_A.end", text(size: 12pt, $arrow(U_A)$), anchor: "south-west")
        content("U_B.end", text(size: 12pt, $arrow(U_B)$), anchor: "north-west")
        content("U_C.end", text(size: 12pt, $arrow(U_C)$), anchor: "north-east")

        line("U_B.end", "U_A.end", name: "U_AB")
        line("U_A.end", "U_C.end", name: "U_AC")
        line("U_C.end", "U_B.end", name: "U_BC")

        content("U_AB.mid", text(size: 12pt, $arrow(U_(A B))$), anchor: "west")
        content("U_BC.mid", text(size: 12pt, $arrow(U_(B C))$), anchor: "north")
        content("U_AC.mid", text(size: 12pt, $arrow(U_(A C))$), anchor: "east")
    })))

    align(center, figure(
        kind: image,
        caption:
			[Векторная диаграмма цепи не симметричной #star  с нейтральным проводом.],

        cetz.canvas({
        import cetz.draw: *

        set-style(content: (frame: "rect", stroke: none, fill: none, padding: 0.3))
        set-style(mark: (end: "straight"))
        line((0,-s), (0,s), name: "OY")
        line((s,0), (-s,0), name: "OX")
        content("OY.end", text(size: 12pt, $+1$), anchor: "west")
        content("OX.end", text(size: 12pt, $+j$), anchor: "south")

        let r_1 = 0.1*s;
        let r_a = r_1 * 4.4;
        let r_b = r_1 * 2;
        let r_c = r_1 * 1.5;

        line((0,0), (angle:  90deg, radius: r_a), stroke: green, name: "I_A")
        line((0,0), (angle: 330deg, radius: r_b), stroke: blue,  name: "I_B")
        line((0,0), (angle: 210deg, radius: r_c), stroke: red,   name: "I_C")

        line((0,0), ((a,b,c) => cetz.vector.add(cetz.vector.add(a, b), c),
                "I_A.end", "I_B.end", "I_C.end"),
            stroke: orange, name: "I_N")


        content("I_A.end", text(size: 12pt, $arrow(I_A)$), anchor:"north-west")
        content("I_B.end", text(size: 12pt, $arrow(I_B)$), anchor:"west")
        content("I_C.end", text(size: 12pt, $arrow(I_C)$), anchor:"east")
        content("I_N.end", text(size: 12pt, $arrow(I_N)$), anchor:"north-west")

    	let r_u = 0.7*s;
        line((0,0), (angle:  90deg, radius: r_u), stroke: green, name: "U_A")
        line((0,0), (angle: 330deg, radius: r_u), stroke: blue,  name: "U_B")
        line((0,0), (angle: 210deg, radius: r_u), stroke: red,   name: "U_C")

        content("U_A.end", text(size: 12pt, $arrow(U_A)$), anchor: "south-west")
        content("U_B.end", text(size: 12pt, $arrow(U_B)$), anchor: "north-west")
        content("U_C.end", text(size: 12pt, $arrow(U_C)$), anchor: "north-east")

        line("U_B.end", "U_A.end", name: "U_AB")
        line("U_A.end", "U_C.end", name: "U_AC")
        line("U_C.end", "U_B.end", name: "U_BC")

        content("U_AB.mid", text(size: 12pt, $arrow(U_(A B))$), anchor: "west")
        content("U_BC.mid", text(size: 12pt, $arrow(U_(B C))$), anchor: "north")
        content("U_AC.mid", text(size: 12pt, $arrow(U_(A C))$), anchor: "east")
    })))

    align(center, figure(
        kind: image,
        caption: 
			[Векторная диаграмма симметричной цепи #star без нейтрального провода.],

        cetz.canvas({
        import cetz.draw: *

        set-style(content: (frame: "rect", stroke: none, fill: none, padding: 0.3))
        set-style(mark: (end: "straight"))
        line((0,-s), (0,s), name: "OY")
        line((s,0), (-s,0), name: "OX")
        content("OY.end", text(size: 12pt, $+1$), anchor: "west")
        content("OX.end", text(size: 12pt, $+j$), anchor: "south")

    	let r_i = 0.5*s;
        line((0,0), (angle:  90deg, radius: r_i), stroke: green, name: "I_A")
        line((0,0), (angle: 330deg, radius: r_i), stroke: blue,  name: "I_B")
        line((0,0), (angle: 210deg, radius: r_i), stroke: red,   name: "I_C")

        content("I_A.end", text(size: 12pt, $arrow(I_A)$), anchor: "north-west")
        content("I_B.end", text(size: 12pt, $arrow(I_B)$), anchor: "east")
        content("I_C.end", text(size: 12pt, $arrow(I_C)$), anchor: "west")

    	let r_u = 0.7*s;
        line((0,0), (angle:  90deg, radius: r_u), stroke: green, name: "U_A")
        line((0,0), (angle: 330deg, radius: r_u), stroke: blue,  name: "U_B")
        line((0,0), (angle: 210deg, radius: r_u), stroke: red,   name: "U_C")

        content("U_A.end", text(size: 12pt, $arrow(U_A)$), anchor: "south-west")
        content("U_B.end", text(size: 12pt, $arrow(U_B)$), anchor: "north-west")
        content("U_C.end", text(size: 12pt, $arrow(U_C)$), anchor: "north-east")

        line("U_B.end", "U_A.end", name: "U_AB")
        line("U_A.end", "U_C.end", name: "U_AC")
        line("U_C.end", "U_B.end", name: "U_BC")

        content("U_AB.mid", text(size: 12pt, $arrow(U_(A B))$), anchor: "west")
        content("U_BC.mid", text(size: 12pt, $arrow(U_(B C))$), anchor: "north")
        content("U_AC.mid", text(size: 12pt, $arrow(U_(A C))$), anchor: "east")
    })))

    align(center, figure(
        kind: image,
        caption:
        [Векторная диаграмма симметричной цепи #star без нейтрального провода.],

        cetz.canvas({
        import cetz.draw: *

        set-style(content: (frame: "rect", stroke: none, fill: none, padding: 0.3))
        set-style(mark: (end: "straight"))
        line((0,-s), (0,s), name: "OY")
        line((s,0), (-s,0), name: "OX")
        content("OY.end", text(size: 12pt, $+1$), anchor: "west")
        content("OX.end", text(size: 12pt, $+j$), anchor: "south")

        let r_u  = 0.3*s;
        let r_ua = r_u * 146 / 100;
        let r_ub = r_u * 256 / 100;
        let r_uc = r_u * 274 / 100;

        line((0,0), (angle:  90deg, radius: r_ua), stroke: green, name: "U_A")
        line((0,0), (angle: 330deg, radius: r_ub), stroke: blue,  name: "U_B")
        line((0,0), (angle: 210deg, radius: r_uc), stroke: red,   name: "U_C")
        line((0,0), ((a,b,c) => cetz.vector.add(cetz.vector.add(a, b), c), 
                        "U_A.end", "U_B.end", "U_C.end"),
            stroke: orange,   name: "U_N")

        content("U_A.end", text(size: 12pt, $arrow(U_A)$), anchor: "south-west")
        content("U_B.end", text(size: 12pt, $arrow(U_B)$), anchor: "north-west")
        content("U_C.end", text(size: 12pt, $arrow(U_C)$), anchor: "north-east")
        content("U_N.end", text(size: 12pt, $arrow(U_N)$), anchor: "south-east")

        line("U_B.end", "U_A.end", name: "U_AB")
        line("U_A.end", "U_C.end", name: "U_AC")
        line("U_C.end", "U_B.end", name: "U_BC")

        content("U_AB.mid", text(size: 12pt, $arrow(U_(A B))$), anchor: "west")
        content("U_BC.mid", text(size: 12pt, $arrow(U_(B C))$), anchor: "north")
        content("U_AC.mid", text(size: 12pt, $arrow(U_(A C))$), anchor: "east")

        let r_i = 0.3*s;
        let r_a = r_i * 2.9;
        let r_b = r_i * 2.3;
        let r_c = r_i * 1.8;

        line("U_N.end",
            (cetz.vector.add, "U_N.end", (angle:  90deg, radius: r_a)),
            stroke: green, name: "I_A")
        line("U_N.end",
            (cetz.vector.add, "U_N.end", (angle: 330deg, radius: r_b)),
            stroke: blue,  name: "I_B")
        line("U_N.end",
            (cetz.vector.add, "U_N.end", (angle: 210deg, radius: r_c)),
            stroke: red,   name: "I_C")

        line("U_N.end", ((a,b,c,o) =>  cetz.vector.add(
                    cetz.vector.add(cetz.vector.add(a, b), c), o),
                (angle:  90deg, radius: r_a), 
                (angle: 330deg, radius: r_b),
                (angle: 210deg, radius: r_c),
                "U_N.end"),
            stroke: orange, name: "I_N")


        content("I_A.end", text(size: 12pt, $arrow(I_A)$), anchor:"east")
        content("I_B.end", text(size: 12pt, $arrow(I_B)$), anchor:"west")
        content("I_C.end", text(size: 12pt, $arrow(I_C)$), anchor:"east")
        content("I_N.end", text(size: 12pt, $arrow(I_N)$), anchor:"north-west")

    })))
    })

#let triangle = "«Треугольник»"
=== Соединение #triangle
+ Цепь
    #figure(caption: [Цепь #triangle. ], image("./circuit2.png"))

+  Расчётные и эксперементальные данные:
    #figure(
        kind: table,
        caption: [Таблица значений цепи #triangle. ],
        tablex(
            map-cells: cell => {
                if cell.y < 2 or cell.x < 2 { 
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
            columns: push_first(range(13).map(it => auto),
                                (1.1cm, 1.5cm)).flatten(),
            rows: (1cm, 1.6cm, auto,),
            align: horizon + center,

            colspanx(2, rowspanx(2, "Режим цепи")),
            colspanx(9, "Измерить"), colspanx(4, "Рассчитать"),

            $U_(A B)$, $U_(A C)$, $U_(B C)$,
            $I_(A B)$, $I_(A C)$, $I_(B C)$,
            $I_A$, $I_B$, $I_C$,
            $P_A$, $P_B$, $P_C$, $P_"эф"$,

            ..transpose(
                push_first(transpose(clear_csv(csv("./result2.csv"))),
                    (
                        (colspanx(2, [симм.])),
                        (rowspanx(2, rotate([несимм.], -90deg)), [обрыв фазы]),
                        ([обрыв фазы])
                    )
                )
            ).flatten()
        )
    )


+ Векторная диаграмма:
	#let s = 5

    #align(center, figure(
        kind: image,
        caption:
        [Векторная диаграмма симметричной цепи #star без нейтрального провода.],

        cetz.canvas({
        import cetz.draw: *

        set-style(content: (frame: "rect", stroke: none, fill: none, padding: 0.3))
        set-style(mark: (end: "straight"))
        line((0,-s), (0,s), name: "OY")
        line((s,0), (-s,0), name: "OX")
        content("OY.end", text(size: 12pt, $+1$), anchor: "west")
        content("OX.end", text(size: 12pt, $+j$), anchor: "south")

        let r_u  = 0.7*s;

        let u_a = (angle:  90deg, radius: r_u);
        let u_b = (angle:  330deg, radius: r_u);
        let u_c = (angle:  210deg, radius: r_u);

        line(u_b, u_a, name: "U_AB")
        line(u_a, u_c, name: "U_AC")
        line(u_c, u_b, name: "U_BC")
        content("U_AB.mid", text(size: 12pt, $arrow(U_(A B))$), anchor:"west")
        content("U_BC.mid", text(size: 12pt, $arrow(U_(B C))$), anchor:"north")
        content("U_AC.mid", text(size: 12pt, $arrow(U_(A C))$), anchor:"east")

        let r_i = 0.7*s;

        line(u_a,
            (cetz.vector.add, u_a, (angle:  245deg, radius: r_i)),
            stroke: green, name: "I_C")

        line(u_b,
            (cetz.vector.add, u_b, (angle: 125deg, radius: r_i)),
            stroke: blue,  name: "I_B")

        line(u_c,
            (cetz.vector.add, u_c, (angle: 5deg, radius: r_i)),
            stroke: red,   name: "I_A")

        line(u_a,
            (cetz.vector.add, u_a, (angle:  260deg, radius: r_i)),
            stroke: black, name: "I_AC")

        line(u_b,
            (cetz.vector.add, u_b, (angle: 140deg, radius: r_i)),
            stroke: black, name: "I_BC")

        line(u_c,
            (cetz.vector.add, u_c, (angle: 20deg, radius: r_i)),
            stroke: black, name: "I_AB")


        content("I_A.end", text(size: 12pt, $arrow(I_A)$), anchor:"east")
        content("I_B.end", text(size: 12pt, $arrow(I_B)$), anchor:"west")
        content("I_C.end", text(size: 12pt, $arrow(I_C)$), anchor:"east")

        content("I_AB.end", text(size: 12pt, $arrow(I_{A B})$),
                anchor:"west")
        content("I_AC.end", text(size: 12pt, $arrow(I_{A C})$),
                anchor:"north")
        content("I_BC.end", text(size: 12pt, $arrow(I_{B C})$),
                anchor:"south")

    })))

== Вывод

В ходе лабораторной работы я изучил различные схемы
соединения трёхфазных цепей: #star, #triangle.

Проведённые эксперименты подтверждают теоретические
соотношения между фазными и линейными напряжениями и токами. По
результатам измерений видно, что для симметричных режимов
трёхфазных цепей линейные и фазные величины находятся в
определенной зависимости.

Векторные диаграммы демонстрируют изменения в напряжениях
и токах при различных условиях, таких как наличие или отсутствие
нейтрального провода и при возникновении обрывов фаз и линий.
