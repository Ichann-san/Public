#!/bin/bash

yesterday=$(date -d "yesterday" '+%Y%m%d%H')
time_12_hours_ago=$(date -d "12 hours ago" '+%Y%m%d%H')
directory="/home/ubuntu/metrics"

for file in "$directory"/metrics_agg_*.log ; do 
    times=$(echo "$file" | sed -E 's/[^0-9 ]//g')
    if [[ $times -le $time_12_hours_ago && $times -ge $yesterday ]]; then
        #echo working
	#echo "$file" >> /home/ubuntu/cleanup.log
        rm "$file"
    fi
done
