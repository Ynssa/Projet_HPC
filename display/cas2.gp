set xlabel "x"
set ylabel "y"
set zlabel "U(x, y)"

splot "output/cas2.out" using 3:4:5, sin(x)+cos(y)
pause mouse close