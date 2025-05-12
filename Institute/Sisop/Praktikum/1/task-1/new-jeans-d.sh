#!/bin/bash

awk -F',' '
NR > 1 {
    device = $7
    gsub(/^[ \t\r]+|[ \t\r]+$/, "", device) 
    totdevice[device]++
    totStreamDuration[device] += $4
}
END {
    max_stream = 0
    max_device = 0
    max_ratio = 0

    topstream = ""
    top_device = ""
    top_ratio = ""

    printf "Jumlah pengguna untuk setiap device\n"
    for (device in totdevice) {
        printf "%-10s : %d\n", device, totdevice[device]
    }

    printf "Durasi tiap device\n"
    for (device in totStreamDuration) {
        printf "%-10s : %d\n", device, totStreamDuration[device]
        if (totdevice[device] > max_device) {
            max_device = totdevice[device]
            top_device = device
        }

        if (totStreamDuration[device] > max_stream) {
            max_stream = totStreamDuration[device]
            topstream = device
        }

        ratio = totStreamDuration[device] / totdevice[device]
        if (ratio > max_ratio) {
            max_ratio = ratio
            top_ratio = device
        }
    }

    printf "\nDevice terpopuler (jumlah kemunculan): %s\n", top_device
    printf "Device menang durasi (total durasi): %s\n", topstream
    printf "Device ter-loyal (rasio durasi/kemunculan): %s\n", top_ratio
}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv

