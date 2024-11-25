set terminal png
set output "plot1.png"

set ylabel "I, А"
set xlabel "R, Ом"

plot 'plot.csv' using 1:2 with lp pt 7 smooth bezier ti "I(R_n), А"


