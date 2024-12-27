set terminal 'png'
set output 'plot3.png'


set ylabel 'n_я об/мин'
set xlabel 'M Ом'

plot \
	'o0.csv' u 5:3 skip 1  w lp t 'n_я (M_1)', \
	'o1.csv' u 5:3 skip 1 w lp t 'n_я (M_2)', \
	'o2.csv' u 5:3 skip 1 w lp t 'n_я (M_3)', \
	'o3.csv' u 5:3 skip 1 w lp t 'n_я (M_4)', \
	'o4.csv' u 5:3 skip 1 w lp t 'n_я (M_5)', \
	'o5.csv' u 5:3 skip 1 w lp t 'n_я (M_6)'
