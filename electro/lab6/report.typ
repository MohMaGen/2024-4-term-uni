#import "@preview/tablex:0.0.9": tablex, rowspanx, colspanx, vlinex, hlinex
#import "../common.typ": transpose, push_first, clear_csv

= ДВИГАТЕЛЬ ПОСТОЯННОГО ТОКА

== Цель

+ Изучить устройство, принцип действия, схемы возбуждения и
    режимы работы двигателя постоянного тока.

+ Выбрать параметры двигателя постоянного тока параллельного
    возбуждения и снять его характеристики.

+ Записать выводы по результатам.

== Ход работы

+ Посчитать цепь:

    #figure(
        image("./circuit1.png")
    )

+ Заполнить таблицу

    #let prep_data(from, to) = {
        let data = clear_csv(csv("./result.csv"))
		let res  = ()

        
        for i in range(from, to) {
            let slice = data.slice(i*8, (i+1)*8)

            if res == () {
                res = slice
            }
            else {
                for j in range(8) {
                    for k in range(5) {
                        res.at(j).push(slice.at(j).at(k))
                    }
                }
            }
        }


        for i in range((to - from) * 5) {
            if (calc.rem(i, 5) == 0) {
                res.at(0).at(i) = rowspanx(8, res.at(0).at(i))

                for j in range(1, 8) {
                    res.at(j).at(i) = ()
                }
            }
        }

        res
    }
    

    #figure(
        kind: table,
        tablex(
            map-cells: cell => {
                cell.content = {
                    set text(size: 10pt)
                    cell.content   
                }
                cell
            },
            columns: range(15).map(it => auto),
			align: horizon + center,

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            ..(prep_data(0, 3)).flatten(),

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            block(inset: (y: 0.5cm), rotate(-90deg, [*$R_"Я", "Ом"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$Delta t, "c"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$n_"Я", "об" / "мин"$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$I_"Я", A$*])),
            block(inset: (y: 0.5cm), rotate(-90deg, [*$M, Н dot.c м$*])),

            ..(prep_data(3, 6)).flatten()
        )
    )

+ Графики

    #figure( image("./plot1.png") )
    #figure( image("./plot2.png") )
    #figure( image("./plot3.png") )

== Вывод

Во время лабораторного эксперимента изучались конструкция, принцип работы, схемы возбуждения и режимы работы двигателя постоянного тока. Двигатель состоит из статора, ротора, щёток и коллекторов, и его работа основана на взаимодействии магнитного поля и тока, проходящего через обмотки ротора, что приводит к вращению вала.

Были выбраны параметры двигателя постоянного тока параллельного возбуждения, и были зарегистрированы его характеристики, такие как число оборотов якоря, ток и момент. Таблицы показывают, что скорость якоря двигателя меняется в зависимости от приложенного напряжения и характеристик нагрузки в зависимости от сопротивления.

Построенные графики зависимостей показывают, что при увеличении тока увеличивается момент двигателя, что типично для двигателей постоянного тока.

В заключение, лабораторная работа обеспечила всеобъемлющее понимание конструкции, принципа работы и характеристик производительности двигателя постоянного тока, которые могут быть использованы для различных приложений, требующих управляемого движения.
