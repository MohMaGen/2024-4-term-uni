set terminal 'png'
set output 'plot2.png'

set xlabel 'I_2, A'
set ylabel 'P_2, Вт'

plot 'result.csv' u 6:7 w lp t 'P_2(I_2)'
