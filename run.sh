#!/bin/bash

echo "$1" 
ffmpeg -i "$1" data/image%d.ppm
AMOUNT_OF_FILES=`find -L data -name '*.ppm' | wc -l`

mpirun ./project $AMOUNT_OF_FILES
AMOUNT_OF_FILES=`find -L data -name '*.pgm' | wc -l`
ffmpeg -y -framerate 60 -i data/image%d.pgm -c:v libx264 -crf 25 -vf "format=yuv420p" -movflags +faststart data/output.mp4
rm data/*.ppm data/*.pgm
