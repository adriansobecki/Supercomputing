#!/bin/bash

echo "$1" 
ffmpeg -i "$1" data/image%d.ppm
AMOUNT_OF_FILES=`find -L data -name '*.ppm' | wc -l`

./project $AMOUNT_OF_FILES
AMOUNT_OF_FILES=`find -L data -name '*.pgm' | wc -l`
if ["$AMOUNT_OF_FILES"==0]; then
  ffmpeg -framerate 60 -i data/image%d.ppm -c:v libx264 -crf 25 -vf "format=yuv420p" -movflags +faststart data/output.mp4
else
  ffmpeg -framerate 60 -i data/image%d.pgm -c:v libx264 -crf 25 -vf "format=yuv420p" -movflags +faststart data/output.mp4
fi
rm data/*.ppm data/*.pgm
