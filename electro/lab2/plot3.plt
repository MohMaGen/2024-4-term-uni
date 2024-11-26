
set terminal png
set output 'plot3.png'

set xlabel 'f, Гц'
set ylabel 'X_L, X_C, Ом'

plot\
    'data2.csv' using 1:2 with lp pt 7 smooth bezier ti 'экс. X_L(f), Ом',\
    'data2.csv' using 1:6 with lp pt 7 smooth bezier ti 'экс. X_C(f), Ом',\
    'data2.csv' using 1:5 with lp pt 7 smooth bezier ti 'рас. X_L(f), Ом',\
    'data2.csv' using 1:9 with lp pt 7 smooth bezier ti 'рас. X_C(f), Ом'
