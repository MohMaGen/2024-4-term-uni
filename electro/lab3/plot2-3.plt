set terminal 'png'
set output 'plot2-3.png'


set xlabel 'C, [мкФ]'
set ylabel 'φ, [рад]'

plot 'output2.csv' using 1:11 w lp lw 2 pt 7 t 'cos φ, [рад]'
