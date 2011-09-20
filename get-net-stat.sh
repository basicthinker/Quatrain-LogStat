#! /bin/bash

PORTs='3000 3100 3200'

LOG_FILE='net-stat-'`date +%s`'.csv'

echo '# [PortNum, Recv-Q, Send-Q]...' > $LOG_FILE

while [ 1 ]
do
  NET_USAGE=`netstat -nat | awk -v ports_str="$PORTs" '
    BEGIN{
      len=split(ports_str, ports, " ");
      for (i=1; i<=len; i++) {
        regex[i]=":"ports[i]
        recv_q[i]=0;
        send_q[i]=0;
        cnt[i]=0;
      }
    }
    {
      for (i=1; i<=len; i++) {
        if ($4~regex[i]) {
          recv_q[i]+=$2;
          send_q[i]+=$3;
          cnt[i]+=1;
        }
      }
    }
    END{
      for (i=1; i<=len; i++) {
        print cnt[i] "\t" recv_q[i] "\t" send_q[i] "\t"
      }
    }'`

  MILL_TIME=$((`date +%s%N`/1000000))

  echo -e $MILL_TIME'\t'$NET_USAGE >> $LOG_FILE
  sleep 0.8
done
exit 0

