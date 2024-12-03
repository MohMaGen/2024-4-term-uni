set terminal 'png'
set output 'plot1-5.png'


plot\
    './output.csv' using 1:11 with l ti 'P, [Вт]',\
    './output.csv' using 1:11 ti '',\
    './output.csv' using 1:13 with l ti 'S, [Вт]',\
    './output.csv' using 1:13 ti ''

