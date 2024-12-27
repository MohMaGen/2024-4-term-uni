set terminal 'png'
set output 'plot1.png'


set ylabel 'n_я об/мин'
set xlabel 't с'

plot \
	'o0.csv' u 2:3  w lp t 'n_я (t_1)', \
	'o1.csv' u 2:3  w lp t 'n_я (t_2)', \
	'o2.csv' u 2:3  w lp t 'n_я (t_3)', \
	'o3.csv' u 2:3  w lp t 'n_я (t_4)', \
	'o4.csv' u 2:3  w lp t 'n_я (t_5)', \
	'o5.csv' u 2:3  w lp t 'n_я (t_6)'
