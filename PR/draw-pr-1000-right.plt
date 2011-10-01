set terminal postscript font 18 eps
set output "eva-micro-high-1000-right.eps"
set size 1,0.8
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
