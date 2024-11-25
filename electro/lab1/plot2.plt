set terminal png
set output "plot2.png"

set ylabel "P, Вт"
set xlabel "R, Ом"

plot 'plot.csv' using 1:3 with lp pt 7 smooth bezier ti 'P_{ист}(R_n), Вт'


