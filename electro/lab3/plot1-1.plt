set terminal 'png'
set output 'plot1-1.png'


plot './output.csv' using 1:2 with l ti 'I, [А]',\
	 './output.csv' using 1:2 ti ''
