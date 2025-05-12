#!/bin/bash

ymdh=`date '+%Y%m%d%H'`
cd /home/ubuntu/metrics/
touch uptime_"$ymdh".log
chmod 600 uptime_"$ymdh".log

temp1=$(uptime | awk -F ',' '{print $1}')

temp2=$(cat /proc/loadavg | awk -F' ' '{print $1,$2,$3}' | tr -s ' ' ',' )

temp3=$(echo "$temp1,$temp2")
echo "uptime,load_avg_1min,load_avg_5min,load_avg_15min" > uptime_"$ymdh".log
echo "$temp3" >> uptime_"$ymdh".log

