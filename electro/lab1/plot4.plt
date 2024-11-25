set terminal png
set output 'plot4.png'

set xlabel 'R, Ом'
set ylabel 'η, %'

plot 'plot.csv' using 1:5 with lp smooth bezier ti 'η(R), %'
