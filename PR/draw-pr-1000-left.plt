set terminal postscript font 18 eps
set output "eva-micro-high-1000-left.eps"
set size 1,0.8
set rmarg 3
set xrange [0:25]
set xlabel 'Number of returns'
set yrange [10:100000]
set ylabel "AAT (ms)"
set logscale y
set ytics nomirror
set y2range [1:100000]
set y2tics format ""
set logscale y2
set key left bottom
plot "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:2 axes x1y1 title '' with lines lt 3, \
    "hprose-t1000-r24-PR-p3000@1694050971.table" using 1:2:3 axes x1y1 title 'TB AAT' with yerrorbars lt 3, \
    984.72 axes x1y1 title '' with lines lt 3, \
    "hprose-t1000-r24-PR-p3000@1694050971.usage" using 1:3 axes x1y2 title 'TB #' with linespoints lt 2, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:2 axes x1y1 title '' with lines lt 1, \
    "hprose-t1000-r24-PR-p3100@1729448414.table" using 1:2:3 axes x1y1 title 'EB AAT' with yerrorbars lt 1, \
    79311.5 axes x1y1 title '' with lines lt 1, \
    "hprose-t1000-r24-PR-p3100@1729448414.usage" using 1:3 axes x1y2 title 'EB #' with linespoints lt 4
