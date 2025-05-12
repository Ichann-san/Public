#!/bin/bash

awk -F'[, ]' '
NR==FNR {
    if(NR > 1) {
        user[$1][$2]=$3
    }
    next
}

{
    if($9 == 500) {
        split($1, ip, ".")
        
        split($4, time, ":")
        gsub(/\[/, "", time[1])

        split(time[1], date, "/")

        bulankenomor["Jan"] = "01"; bulankenomor["Feb"] = "02"; bulankenomor["Mar"] = "03"; bulankenomor["Apr"] = "04"; bulankenomor["May"] = "05"; bulankenomor["Jun"] = "06";
        bulankenomor["Jul"] = "07"; bulankenomor["Aug"] = "08"; bulankenomor["Sep"] = "09"; bulankenomor["Oct"] = "10"; bulankenomor["Nov"] = "11"; bulankenomor["Dec"] = "12";

        date_format=bulankenomor[date[2]] "/" date[1] "/" date[3]

        if (date_format in user && ip[4] in user[date_format]) {
            print user[date_format][ip[4]]
        }

    }
}' peminjaman_computer.csv access.log | sort | uniq -c | sort -r | head -1 | awk -F' ' '{print "Orang yang menemukan Error Code 500 terbanyak: " $2 "\nDengan jumlah Error Code 500 sebanyak: " $1}'

# path peminjaman_computer.csv dan access.log dapat diubah tergantung dengan tempat disimpannya file
