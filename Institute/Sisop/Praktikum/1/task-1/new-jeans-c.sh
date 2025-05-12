!/bin/bash
top_song=$(awk -F',' '$2 ~ /[0-9]/ {count[$3]++}
END {
    max_count = 0
    top_song = ""
    for (song in count) {
        if (count[song] > max_count) {
            max_count = count[song]
            top_song = song
        }
    }
print top_song
  }' Documents/NewJeans/newjeans_analysis/DataStreamer.csv)

awk -v top_song="$top_song" -F',' '$2 == top_song {printf "Top song : %s\nAlbum : %s\nRelease year : %s\n", top_song, $1, $3}' Documents/NewJeans/newjeans_analysis/AlbumDetails.csv


