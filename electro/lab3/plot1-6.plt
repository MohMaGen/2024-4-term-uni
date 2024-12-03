set terminal 'png'
set output 'plot1-6.png'


plot\
    './output.csv' using 1:12 with l ti 'Q, [Вт]',\
    './output.csv' using 1:12 ti ''

