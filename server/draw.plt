# Draw SE with 100/1k/10k tasks.
set terminal eps
set output 'SRSE-100.eps'
set xlabel 'Number of returns'
set xrange [0:25]
set ylabel 'Latency (ms)'
set yrange [0:200]
set y2label '% CPU usage per core'
set y2range [0:100]
plot "SRSE-TB-100.in" using 1:2 axes x1y1 title 'Thread-based' with linespoints, \
    "SRSE-TB-100.in" using 1:4 axes x1y2 title 'TB CPU' with linespoints, \
    "SRSE-EB-100.in" using 1:2 axes x1y1 title 'Event-based' with linespoints, \
    "SRSE-EB-100.in" using 1:4 axes x1y2 title 'EB CPU' with linespoints, \
    "SRSE-100-ideal.in" using 1:2 axes x1y1 title 'Ideal' with linespoints

