set terminal png
set output "plot3.png"

set ylabel "P_{наг}, Вт"
set xlabel "R, Ом"

plot 'plot.csv' using 1:4 with lp smooth bezier ti "P_{наг}(R), Вт"
