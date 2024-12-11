set terminal 'png'
set output 'plot1-7.png'


set arrow from -280,0 to 280,0 lc rgb 'black' lw 1 filled
set arrow from 0,-280 to 0,280 lc rgb 'black' lw 1 filled

set arrow from 0,0 to 220,0 lc rgb 'blue' lw 3
set arrow from 0,0 to 0,230 lc rgb 'red' lw 3
set arrow from 0,0 to 0,-235 lc rgb 'green' lw 3

set label "U_{ R} = 220 [В]"   at 170,20
set label "U_{ L} = 230j [В]"  at -110,230
set label "U_{ C} = -235j [В]" at -120,-235

set label "j" at -10,280
set label "U" at 280,-20

set xlabel 'U_{ R}, [В]'
set ylabel 'U_{ L}, U_{ C}, [В]'

set xrange [-300:300]
set yrange [-300:300]

plot NaN t ''
