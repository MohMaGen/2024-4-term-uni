set terminal png
set output 'plot1.png'

set xlabel 'f, Гц'
set ylabel 'X_L, X_C, Ом'

plot\
    'data2.csv' using 1:2 with lp pt 7 smooth bezier ti 'X_L(f), Ом',\
    'data2.csv' using 1:6 with lp pt 7 smooth bezier ti 'X_C(f), Ом'
	

