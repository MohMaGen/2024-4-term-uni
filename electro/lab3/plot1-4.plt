set terminal 'png'
set output 'plot1-4.png'


plot\
    './output.csv' using 1:6 with l ti 'R, [Ом]',\
    './output.csv' using 1:6 ti '',\
    './output.csv' using 1:9 with l ti 'Z, [Ом]',\
    './output.csv' using 1:9 ti '',\

