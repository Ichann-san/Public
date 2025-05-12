#!/bin/bash

time=`date '+%Y%m%d%H%M%S' `
cd /home/ubuntu/metrics/
touch metrics_"$time".log
chmod 600 metrics_"$time".log

mem=$(free -m | sed -E 's/[^0-9 ]//g'|tr -s ' ' '\n' )

path=$(du -sh /home/ubuntu/ | awk '{print $2,$1}')

echo "mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" > metrics_"$time".log

echo "$mem" "$path" | tr -s '\n' ',' | tr -s ' ' ',' | sed 's/^,//;s/,$//' >> metrics_"$time".log
