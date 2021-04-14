#Set the output to a png file
set terminal png size 400,400
#The file we'll write to
set output 'sinx.png'
# The graphic title
set title 'Sin(x)'
#plot the graphic
plot sin(x)
pause -1

