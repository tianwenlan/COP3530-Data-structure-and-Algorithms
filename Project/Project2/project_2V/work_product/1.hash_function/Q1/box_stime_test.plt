set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 500, 350 
set output 'box_stime_test.png'
set boxwidth 0.2 absolute
set title "box-and-whisker with median bar and whiskerbars" 
set xrange [ 0 : 5]
set yrange [ 0 : 12.5] 
plot 'box_stime_test2.dat' using 1:3:2:6:5:xticlabels(7) with candlesticks lt 3 lw 2 title 'Quartiles' whiskerbars,      ''                 using 1:4:4:4:4 with candlesticks lt -1 lw 2 notitle