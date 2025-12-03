set xlabel "x"
set ylabel "y"
set zlabel "U(x, y)"

splot for [f in system("ls output/cas2.out.4.*")] f using 3:4:5 title f, sin(x)+cos(y)

pause mouse close