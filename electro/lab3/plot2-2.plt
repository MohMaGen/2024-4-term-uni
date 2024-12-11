set terminal 'png'
set output 'plot2-2.png'

set xlabel 'C, [мкФ]'
set ylabel 'Y, G, [См]'

plot\
    'output2.csv' using 1:6 w lp lw 2 pt 7 t 'Y, [См]', \
    'output2.csv' using 1:7 w lp lw 2 pt 7 t 'G, [См]'
