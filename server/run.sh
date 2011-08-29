#! /bin/sh

make

# all depending on file.list

./log-stat # generates check.stat, LogFileName.latency, and LogFileName.interval

# depending on LogFileName.latency 
./gen-plt-table # generates LogFileName.table

# depending on LogFileName.interval and cpu/network usage logs
./gen-raw-usage

./gen-plt-usage
