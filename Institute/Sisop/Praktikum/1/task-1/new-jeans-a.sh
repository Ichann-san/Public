#!/bin/bash

awk -F',' '{print $2}' Documents/NewJeans/newjeans_analysis/DataStreamer.csv | sort | grep "2" | grep -v "_" | awk '{print; ++n} END { print "Total :", n }'

