#! /bin/bash

if [ $# -ne 1 ]; then
  echo 'Please enter process name.'
  exit 1
fi

LOG_FILE='cpu-usage-'`date +%s`'.csv'

PIDs_STR=`pidof $1`
if [ -z "$PIDs_STR" ]; then
  echo 'No pids with such proccess name.'
  exit 1
fi

echo '# TimeMillions '$PIDs_STR > $LOG_FILE

PIDs_STR=${PIDs_STR//' '/','}

while [ 1 ]
do
  CPU_USAGE=`top -p$PIDs_STR -n 1 -b | awk '
    BEGIN{
      len=split("'$PIDs_STR'", pids, ",");
      for (i=1; i<=len; i++) {
        usage[i]=0;
      }
    }
    {
      for (i=1; i<=len; i++) {
        if ($1==pids[i]) {
          usage[i]=$9;
        }
      }
    }
    END{
      for (i=1; i<=len; ++i) {
        print usage[i] "\t"
      }
    }'`

  MILL_TIME=$((`date +%s%N`/1000000))

  echo -e $MILL_TIME'\t'$CPU_USAGE >> $LOG_FILE
  sleep 0.5
done
exit 0

