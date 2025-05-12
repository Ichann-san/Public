#!/bin/bash

ymdh=`date '+%Y%m%d%H'`
direktori="/home/ubuntu/metrics"

time_1h_ago=$(date -d "1 hour ago" '+%Y%m%d%H%M%S')
time=$(date +%Y%m%d%H%M%S)

cd /home/ubuntu/metrics
touch metrics_agg_"$ymdh".log
chmod 600 metrics_agg_"$ymdh".log

max=(0 0 0 0 0 0 0 0 0)
min=(9999999 9999999 9999999 9999999 9999999 9999999 9999999 9999999 9999999)
sum=(0 0 0 0 0 0 0 0 0)
count=0  
maxpath=0
minpath=9999999
sumpath=0

for file_log in "$direktori"/metrics_20*.log; do        
	times=$(echo "$file_log" | sed -E 's/[^0-9 ]//g')        
        if [[ $times -ge $time_1h_ago && $times -lt $time ]]; then
        #echo "Processing: $file_log"
	mem_tot=$(awk -F',' 'NR > 1{print $1}' "$file_log")
        mem_used=$(awk -F',' 'NR > 1{print $2}' "$file_log")
        mem_free=$(awk -F',' 'NR > 1{print $3}' "$file_log")
        mem_shared=$(awk -F',' 'NR > 1{print $4}' "$file_log")
        mem_buff=$(awk -F',' 'NR > 1{print $5}' "$file_log")
        mem_available=$(awk -F',' 'NR > 1{print $6}' "$file_log")
        swap_tot=$(awk -F',' 'NR > 1{print $7}' "$file_log")
        swap_used=$(awk -F',' 'NR > 1{print $8}' "$file_log")
        swap_free=$(awk -F',' 'NR > 1{print $9}' "$file_log")
	path=$(awk -F',' 'NR > 1{print $10}' "$file_log")
        path_size=$(awk -F',' 'NR > 1{print $11}' "$file_log" | sed 's/M//')	

        max[0]=$((mem_tot > max[0] ? mem_tot : max[0]))
        min[0]=$((mem_tot < min[0] ? mem_tot : min[0]))
        sum[0]=$((sum[0] + mem_tot))

        max[1]=$((mem_used > max[1] ? mem_used : max[1]))
        min[1]=$((mem_used < min[1] ? mem_used : min[1]))
        sum[1]=$((sum[1] + mem_used))

        max[2]=$((mem_free > max[2] ? mem_free : max[2]))
        min[2]=$((mem_free < min[2] ? mem_free : min[2]))
        sum[2]=$((sum[2] + mem_free))

        max[3]=$((mem_shared > max[3] ? mem_shared : max[3]))
        min[3]=$((mem_shared < min[3] ? mem_shared : min[3]))
        sum[3]=$((sum[3] + mem_shared))

        max[4]=$((mem_buff > max[4] ? mem_buff : max[4]))
        min[4]=$((mem_buff < min[4] ? mem_buff : min[4]))
        sum[4]=$((sum[4] + mem_buff))

        max[5]=$((mem_available > max[5] ? mem_available : max[5]))
        min[5]=$((mem_available < min[5] ? mem_available : min[5]))
        sum[5]=$((sum[5] + mem_available))

        max[6]=$((swap_tot > max[6] ? swap_tot : max[6]))
        min[6]=$((swap_tot < min[6] ? swap_tot : min[6]))
        sum[6]=$((sum[6] + swap_tot))

        max[7]=$((swap_used > max[7] ? swap_used : max[7]))
        min[7]=$((swap_used < min[7] ? swap_used : min[7]))
        sum[7]=$((sum[7] + swap_used))

        max[8]=$((swap_free > max[8] ? swap_free : max[8]))
        min[8]=$((swap_free < min[8] ? swap_free : min[8]))
        sum[8]=$((sum[8] + swap_free))
	
	maxpath=$((path_size > maxpath ? path_size : maxpath))
        minpath=$((path_size < minpath ? path_size : minpath))
        sumpath=$((sumpath + path_size))

        count=$((count + 1))
	fi

done

if [[ $count -gt 0 ]]; then
    for i in {0..8}; do
        avg[$i]=$(echo "scale=2; ${sum[$i]} / $count" | bc)
	avgpath=$(echo "scale=2; $sumpath / $count" | bc)
    done
fi

echo "type,mem_total,mem_used,mem_free,mem_shared,mem_buff,mem_available,swap_total,swap_used,swap_free,path,path_size" > metrics_agg_"$ymdh".log


echo "minimum,${min[0]},${min[1]},${min[2]},${min[3]},${min[4]},${min[5]},${min[6]},${min[7]},${min[8]},${path},${minpath}M" >> metrics_agg_"$ymdh".log
echo "maximum,${max[0]},${max[1]},${max[2]},${max[3]},${max[4]},${max[5]},${max[6]},${max[7]},${max[8]},${path},${maxpath}M" >> metrics_agg_"$ymdh".log

echo "average,${avg[0]},${avg[1]},${avg[2]},${avg[3]},${avg[4]},${avg[5]},${avg[6]},${avg[7]},${avg[8]},${path},${avgpath}M" >> metrics_agg_"$ymdh".log
