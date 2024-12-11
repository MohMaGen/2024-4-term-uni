set terminal 'png'
set output 'plot2-1.png'

set xlabel 'C, [мкФ]'
set ylabel 'I, I_{ R}, I_{ L}, I_{ C}, [A]'

plot\
    'output2.csv' using 1:2 with lp lw 2 pt 7 t 'I, [A]', \
    'output2.csv' using 1:3 with lp lw 2 pt 7 t 'I_{ R}, [A]', \
    'output2.csv' using 1:4 with lp lw 2 pt 7 t 'I_{ L}, [A]', \
    'output2.csv' using 1:5 with lp lw 2 pt 7 t 'I_{ C}, [A]'

