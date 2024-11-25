set terminal png
set output 'plot2.png'

set xlabel 'f, Гц'
set ylabel 'X_L, X_C, Ом'

plot\
    'data2.csv' using 1:5 with lp pt 7 smooth bezier ti 'X_L(f), Ом',\
    'data2.csv' using 1:9 with lp pt 7 smooth bezier ti 'X_C(f), Ом'
	

