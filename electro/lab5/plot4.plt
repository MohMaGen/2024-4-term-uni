set terminal 'png'
set output 'plot4.png'

set xlabel 'I_2, A'
set ylabel 'η, %'

plot 'result.csv' u 6:9 w lp t 'η'
