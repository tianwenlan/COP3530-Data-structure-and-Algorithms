set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 500, 350 
set output 'histogram_Chi_population.png'
set key inside right top vertical Right noreverse noenhanced autotitles nobox
set datafile missing '-'
set style data linespoints
set xtics border in scale 1,0.5 nomirror rotate by -45  offset character 0, 0, 0 autojustify
set xtics  norangelimit font ",8"
set xtics   ()
set title "Chi-square of different hash function using localities-location" 
i = 22
plot 'hash_Chi_population.dat' using 2:xtic(1) title columnheader(2), for [i=3:14] '' using i title columnheader(i)


# set terminal pngcairo  transparent enhanced font "arial,10" fontscale 1.0 size 500, 350 
# set output 'histogram_Chi.png'
# set boxwidth 0.9 absolute
# set style fill   solid 1.00 border lt -1
# set key inside right top vertical Right noreverse noenhanced autotitles nobox
# set style histogram clustered gap 1 title  off# set character 0, 0, 0
# set datafile missing '-'
# set style data histograms
# set xtics border in scale 0,0 nomirror rotate by -45  off# set character 0, 0, 0 autojustify
# set xtics  norangelimit font ",8"
# set xtics   ()
# set title "Chi-square of different hash function with 13 different capacities"
# set yrange [ 0.00000 : 25000 ] noreverse nowriteback
#i = 22
#plot 'hash_Chi.dat' using 2:xtic(1) ti col, '' u 3 ti col, '' u 4 ti col, '' u 5 ti col, '' u 6 ti col, '' u 7 ti col, '' u 8 ti col, '' u 9 ti col, '' u 10 ti col, '' u 11 ti col, '' u 12 ti col, '' u 13 ti col, '' u 14 ti col