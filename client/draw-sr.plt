# Draw SE with 100/1k/10k tasks.
set terminal postscript
set output 'SRSE-100.eps'
set xlabel 'Number of returns'
set xrange [0:25]
set ylabel 'Latency (ms)'
set yrange [0:110]
set y2label '% CPU usage per core'
set y2range [0:100]
plot "SRSE-TBB100.in" using 1:2 axes x1y1 title 'Thread-based' with linespoints, \
    "SRSE-TBB100.in" using 1:4 axes x1y2 title 'TB CPU' with linespoints, \
    "SRSE-TB100.in" using 1:2 axes x1y1 title 'Event-based' with linespoints, \
    "SRSE-TB100.in" using 1:4 axes x1y2 title 'EB CPU' with linespoints, \
    "SR-100-ideal.in" using 1:2 axes x1y1 title 'Ideal' with linespoints

# set output 'SRPE-100.eps'

