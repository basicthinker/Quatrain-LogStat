# Draw SE with 100/1k/10k tasks.
set origin $2, $3
set xrange [0:25]
set yrange [0:$1*1.1]
set ytics $1*0.2
set ytics nomirror
set y2range [0:100]
set y2tics 10
plot "$0-TB$1.in" using 1:2 axes x1y1 title 'Thread-based' with linespoints ps 1.5, \
    "$0-TB$1.in" using 1:4 axes x1y2 title 'Thread-based CPU' with linespoints ps 1.5, \
    "$0-EB$1.in" using 1:2 axes x1y1 title 'Event-based' with linespoints ps 1.5, \
    "$0-EB$1.in" using 1:4 axes x1y2 title 'Event-based CPU' with linespoints ps 1.5, \
    "$0-$1-ideal.in" using 1:2 axes x1y1 title 'Ideal' with linespoints ps 1.5


