set terminal postscript font 35 eps
set size 1,2.4
set output "eva-micro-low-left.eps"
set rmarg 2
set multiplot
set ylabel 'Sequential-execution AAT (ms)'
set size 1,1.2
set y2tics format ""
call "draw-sr-template.plt" SRSE 100 0 1.2
set bmarg 4
set xlabel 'Number of returns'
set ylabel 'Parallel-execution AAT (ms)'
call "draw-sr-template.plt" SRPE 100 0 0
unset y2tics
unset xlabel
unset ylabel
unset bmarg
unset rmarg
unset multiplot

set terminal postscript font 35 eps
set size 0.9,2.4
set output "eva-micro-low-mid.eps"
set lmarg 5
set rmarg 2
set multiplot
set size 0.9,1.2
set y2tics format ""
call "draw-sr-template.plt" SRSE 1000 0 1.2
set bmarg 4
set xlabel 'Number of returns'
call "draw-sr-template.plt" SRPE 1000 0 0
unset y2tics
unset xlabel
unset bmarg
unset lmarg
unset rmarg
unset multiplot

set terminal postscript font 35 eps
set size 1.1,2.4
set output "eva-micro-low-right.eps"
set lmarg 6
set rmarg 5
set multiplot
set y2label '% CPU usage per core'
set size 1,1.2
set y2tics format "%g"
call "draw-sr-template.plt" SRSE 10000 0 1.2
set bmarg 4
set xlabel 'Number of returns'
call "draw-sr-template.plt" SRPE 10000 0 0
unset xlabel
unset bmarg
unset multiplot
