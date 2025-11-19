set xlabel "x"
set ylabel "y"
set zlabel "U(x, y)"

splot "output/cas1.out" using 3:4:5, x*(1-x)*y*(1-y)
pause mouse close