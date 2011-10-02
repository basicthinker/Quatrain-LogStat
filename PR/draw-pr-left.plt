set terminal postscript font 22 eps
set output "eva-micro-high-left.eps"
set size 1,2

set multiplot
set size 1,1
set origin 0,1
set rmarg 3
set xrange [0:25]
set yrange [10:12000]
set ylabel "100-ms task AAT (ms)"
set logscale y
set ytics nomirror
set y2range [10:20000]
set y2tics format ""
set logscale y2
set key bottom
plot "hprose-t100-r24-PR-p3000@1679368083.table" using 1:2 axes x1y1 title '' with lines lt 2 lw 2, \
    "hprose-t100-r24-PR-p3000@1679368083.table" using 1:2:3 axes x1y1 title 'TB AAT' with yerrorbars lt 2 lw 2, \
    "hprose-t100-r24-PR-p3000@1679368083.usage" using 1:3 axes x1y2 title 'TB #' with linespoints lt 3 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:2 axes x1y1 title '' with lines lt 1 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:2:3 axes x1y1 title 'EB AAT' with yerrorbars lt 1 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.usage" using 1:3 axes x1y2 title 'EB #' with linespoints lt 4 lw 2
unset y2tics

set size 1,1
set origin 0,0
set rmarg 3
set xrange [0:25]
set xlabel 'Number of returns'
set yrange [10:100000]
set ylabel "1000-ms task AAT (ms)"
set logscale y
set ytics nomirror
set y2range [1:100000]
set y2tics format ""
set logscale y2
set key left bottom
plot "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:2 axes x1y1 title '' with lines lt 3 lw 2, \
    "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:2:3 axes x1y1 title 'TB AAT' with yerrorbars lt 3 lw 2, \
    "hprose-t1000-r24-PR-p3000@1694050971.usage" using 1:3 axes x1y2 title 'TB #' with linespoints lt 2 lw 2, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:2 axes x1y1 title '' with lines lt 1 lw 2, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:2:3 axes x1y1 title 'EB AAT' with yerrorbars lt 1 lw 2, \
    "hprose-t1000-r24-PR-p3100@1729448414.usage" using 1:3 axes x1y2 title 'EB #' with linespoints lt 4 lw 2

unset multiplot

#   65.2381 axes x1y1 title '' with lines lt 2 lw 2, \
#   6875.15 axes x1y1 title '' with lines lt 1 lw 2, \

#   984.72 axes x1y1 title '' with lines lt 3 lw 2, \
#   79311.5 axes x1y1 title '' with lines lt 1 lw 2, \
