#set text(font: "Noto Sans Georgian", size: 11pt, spacing: 3pt)
#set par(leading: 1pt)

#show terms: it => {
    pad(left: 30pt, for chld in it.children {
            rect(stroke: 1pt + black, inset: 10pt)[
                #move(dy: -20pt, rect(fill: white)[Term: *#chld.term*])
                #v(-30pt)
                #set text(size: 10pt)
                #chld.description
            ]
        }
    )
}

#show heading: it => {
    set align(center)
    if it.level == 1 {
        set text(size: 24pt)
        it.body
    }
    if it.level == 2 {
        set text(size: 20pt)
        it.body
    }
    if it.level == 3 {
        set text(size: 12pt)
        it.body
    }
}


= Ряды фурье.
#pagebreak()


== Лекция 1
#columns()[
/ Переодическая функция:
        пусть есть функция $y = f(x)$,
        определённая на
        $RR$ ($D(y) = RR$), тогда если для
        $forall T > 0: exists x in RR$ верно следующие:
        $
            f(x + T) = f(x - T) = f(x)
        $
        , то фунция $y = f(x)$ - называется переодической функцией.

/ Главный период:
    пусть дана переодичная функция $y = f(x)$, тогда
    меньший из её периудов называется главным периодом
    функции $y = f(x)$.


=== Свойства переодической функции

+ Пусть дана переодическая функция $y = f(x)$ тогда, если T --- период функции, то
    и $k dot.c T$ --- тоже период функции $y = f(x)$.

+ Пусть дана функция $y = f(x)$ --- T-переодическая тогда, чтобы задать функцию,
    достаточно определить её на отрезке $[a; a + T]$. (Например $[0; T]$).

+ Любая линейная конбинация Т-переодических функций -- Т-переодичная.

+ Пусть дана $f(x)$ --- Т-переодическая, интегрированная на отрезке $[a;b]$, то она
    интегрированая и на любом отрезке $[a+T;b+T]$ и $integral_a^b f(x) d x = integral_(a+T)^(b+T)
    f(x) d x$.

+ Пусть дана $f(x)$ --- Т-переодическая, интегрируемая в области D, тогда все интегралы на отрезках
    длиной Т будут равны. Наример:
    $ limits(integral)_a^(a+T) f(x) d x = limits(integral)_0^T f(x) d x $
]


