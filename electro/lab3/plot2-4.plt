set terminal 'png'
set output 'plot2-4.png'

set arrow from -18,0 to 18,0 lc rgb 'black' lw 1 filled
set arrow from 0,-18 to 0,18 lc rgb 'black' lw 1 filled

set arrow from 0,0 to 15.03,0 lc rgb 'blue' lw 3
set arrow from 0,0 to 0,15.03 lc rgb 'red' lw 3
set arrow from 0,0 to 0,-14.70 lc rgb 'green' lw 3

set label "I_{ R} = 15.03 [A]"   at 10,2
set label "I_{ L} = 15.03j [A]"  at -8,15.03
set label "I_{ C} = -14.70j [A]" at -8.5,-14.70

set label "j" at -1,18
set label "I, [A]" at 17,-2

set xlabel 'I_{ R}, [А]'
set ylabel 'I_{ L}, I_{ C}, [А]'

set xrange [-20:20]
set yrange [-20:20]

plot NaN t ''
