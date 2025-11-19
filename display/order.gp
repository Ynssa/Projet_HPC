set xlabel "dx = dy"
set ylabel "Erreur"

set log x
set log y
plot "output/order.out" using 1:2 with linespoint
pause mouse close