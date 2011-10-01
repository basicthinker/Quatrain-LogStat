set terminal postscript font 18 eps
set output "eva-micro-high-100-left.eps"
set size 1,0.8
set rmarg 3
set xrange [0:25]
set xlabel 'Number of returns'
set yrange [10:12000]
set ylabel "AAT (ms)"
set logscale y
set ytics nomirror
set y2range [10:20000]
set y2tics format ""
set logscale y2
set key bottom
plot "hprose-t100-r24-PR-p3000@1679368083.table" using 1:2 axes x1y1 title '' with lines lt 2, \
    "hprose-t100-r24-PR-p3000@1679368083.table" using 1:2:3 axes x1y1 title 'TB AAT' with yerrorbars lt 2, \
    65.2381 axes x1y1 title '' with lines lt 2, \
    "hprose-t100-r24-PR-p3000@1679368083.usage" using 1:3 axes x1y2 title 'TB #' with linespoints lt 3, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:2 axes x1y1 title '' with lines lt 1, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:2:3 axes x1y1 title 'EB AAT' with yerrorbars lt 1, \
    6875.15 axes x1y1 title '' with lines lt 1, \
    "hprose-t100-r24-PR-p3100@1682793028.usage" using 1:3 axes x1y2 title 'EB #' with linespoints lt 4
unset y2tics