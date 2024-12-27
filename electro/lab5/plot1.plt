set terminal 'png'
set output 'plot1.png'

set xlabel 'I_2, A'
set ylabel 'U_2, B'

plot 'data.csv' u 6:5 w lp t 'U_2(I_2)'
