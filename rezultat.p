#Set the output to a png file
set terminal png size 400,400
#The file we'll write to
set output 'data.png'
# The graphic title
set title 'Media camerelor'
set grid
unset key
set xlabel 'Numarul camerei'
set ylabel 'Media camerei'
#plot the graphic
plot "rez_partiale.txt" with lines lc "violet" lw 3
pause -1

