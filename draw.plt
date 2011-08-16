set terminal png
set output 'OUTPUT_SE.png'
set xlabel 'Number of returns'
set xrange [0:25]
set ylabel 'Latency (ms)'
set yrange [0:2000]
plot "INPUT_FILE" using 1:2 title 'Blocking' with linespoints, \
    "INPUT_FILE" using 1:2:3 title '' with yerrorbars

set output 'OUTPUT_PE.png'
plot "INPUT_FILE" using 1:4 title 'Blocking' with linespoints, \
    "INPUT_FILE" using 1:4:5 title '' with yerrorbars

