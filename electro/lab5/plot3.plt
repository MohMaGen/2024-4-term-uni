set terminal 'png'
set output 'plot3.png'

set xlabel 'I_2, A'
set ylabel 'cos φ'

plot 'result.csv' u 6:8 w lp t 'cosφ(I_2)'
