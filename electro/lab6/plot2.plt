set terminal 'png'
set output 'plot2.png'


set ylabel 'n_я об/мин'
set xlabel 'R_я Ом'

plot \
	'o0.csv' u 1:3  w lp t 'n_я (R_я1)', \
	'o1.csv' u 1:3  w lp t 'n_я (R_я2)', \
	'o2.csv' u 1:3  w lp t 'n_я (R_я3)', \
	'o3.csv' u 1:3  w lp t 'n_я (R_я4)', \
	'o4.csv' u 1:3  w lp t 'n_я (R_я5)', \
	'o5.csv' u 1:3  w lp t 'n_я (R_я6)'
