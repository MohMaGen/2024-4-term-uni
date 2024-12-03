set terminal 'png'
set output 'plot1-2.png'


plot './output.csv' using 1:3 with l ti 'U_{R}, [В]',\
    './output.csv' using 1:3 ti '',\
    './output.csv' using 1:4 with l ti 'U_{L}, [В]',\
    './output.csv' using 1:4 ti '',\
    './output.csv' using 1:5 with l ti 'U_{C}, [В]',\
    './output.csv' using 1:5 ti ''
