#!/bin/bash

awk -F',' '{print $2,$3}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv | awk '$1 ~ /[0-9]/ {print}' | sort |
awk '{ count[$2]++}
END {
    max_count = 0
    top_song = ""
    for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
    if (max_count >= 24) {
        printf "Keren, Minji! Kamu hebat <3!\n"
        printf "Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
 } 
        else {
        printf "Maaf, Minji, total streamingnya tidak sesuai harapan :(\n"
        printf "Lagu yang paling banyak di-streaming : %s, sebanyak : %d user", top_song, max_count
    }
}'




                                                                                                                         




