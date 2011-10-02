set terminal postscript font 22 eps
set output "eva-micro-high-right.eps"
set size 1,2

set multiplot
set size 1,1
set origin 0,1
set xrange [0:25]
set yrange [10:12000]
set ytics format ""
set logscale y
set ytics nomirror
set y2range [10:20000]
set y2label "# active connections"
set y2tics nomirror
set logscale y2
set key at 10,8000
plot "hprose-t100-r24-PR-p3000@1679368083.table" using 1:4 axes x1y1 title '' with lines lt 2 lw 2, \
    "hprose-t100-r24-PR-p3000@1679368083.table" using 1:4:5 axes x1y1 title 'TB AAT' with yerrorbars lt 2 lw 2, \
    23.7439 axes x1y1 title '' with lines lt 2 lw 2, \
    "hprose-t100-r24-PR-p3000@1679368083.usage" using 1:5 axes x1y2 title 'TB #' with linespoints lt 3 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:4 axes x1y1 title '' with lines lt 1 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.table" using 1:4:5 axes x1y1 title 'EB AAT' with yerrorbars lt 1 lw 2, \
    15.0483 axes x1y1 title '' with lines lt 1 lw 2, \
    "hprose-t100-r24-PR-p3100@1682793028.usage" using 1:5 axes x1y2 title 'EB #' with linespoints lt 4 lw 2

set size 1,1
set origin 0,0
set xrange [0:25]
set xlabel 'Number of returns'
set yrange [10:100000]
set ytics format ""
set logscale y
set ytics nomirror
set y2range [1:100000]
set y2label "# active connections"
set y2tics nomirror
set logscale y2
set key default
plot "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:4 axes x1y1 title '' with lines lt 2, \
    "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:4:5 axes x1y1 title 'TB AAT' with yerrorbars lt 2, \
    60.002 axes x1y1 title '' with lines lt 2, \
    "hprose-t1000-r24-PR-p3000@1694050971.usage" using 1:5 axes x1y2 title 'TB #' with linespoints lt 2, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:4 axes x1y1 title '' with lines lt 1, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:4:5 axes x1y1 title 'EB AAT' with yerrorbars lt 1, \
    48.1987 axes x1y1 title '' with lines lt 1, \
    "hprose-t1000-r24-PR-p3100@1729448414.usage" using 1:5 axes x1y2 title 'EB #' with linespoints lt 4

unset multiplot
