#!/bin/bash
START_TIME=`echo $(($(date +%s%N)/1000000))`
ffmpeg -i "$1" data/image%d.ppm
AMOUNT_OF_FILES=`find -L data -name '*.ppm' | wc -l`
echo "Please wait..."
mpirun -np "$2" ./project $AMOUNT_OF_FILES
AMOUNT_OF_FILES=`find -L data -name '*.pgm' | wc -l`
ffmpeg -y -framerate 60 -i data/image%d.pgm -c:v libx264 -crf 25 -vf "format=yuv420p" -movflags +faststart data/output.mp4
rm data/*.ppm data/*.pgm
ELAPSED_TIME=`echo $(($(date +%s%N)/1000000))`
echo $((ELAPSED_TIME - START_TIME))
