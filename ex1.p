#Set the output to a png file
set terminal png size 400,400
#The file we'll write to
set output 'data.png'
# The graphic title
set title 'Rata'
set yrange[0:0.01]
set grid
set xtics 1
set ytics 1
unset key

#plot the graphic
plot "data.txt" with lines lc "violet" lw 3
pause -1

