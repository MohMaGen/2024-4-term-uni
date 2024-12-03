set terminal 'png'
set output 'plot1-3.png'


plot './output.csv' using 1:7 with l ti 'X_L, [Ом]',\
     './output.csv' using 1:7 ti '',\
     './output.csv' using 1:8 with l ti 'X_C, [Ом]',\
     './output.csv' using 1:8 ti '',\
