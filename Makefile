CC=g++
CFLAGS=-Iinc -W -Wall -pedantic


project: obj/main.o obj/video_manager.o obj/image_processing.o
	g++ $(CFLAGS) -o project obj/main.o obj/video_manager.o obj/image_processing.o

obj/main.o: src/main.cpp inc/video_manager.h
	g++ $(CFLAGS) -c -o obj/main.o src/main.cpp

obj/image_processing.o: src/image_processing.cpp inc/image_processing.h 
	g++ $(CFLAGS) -c -o obj/image_processing.o src/image_processing.cpp

obj/video_manager.o: src/video_manager.cpp inc/video_manager.h inc/image_processing.h
	g++ $(CFLAGS) -c -o obj/video_manager.o src/video_manager.cpp -I/usr/local/opencv/gcc-4.9.2/3.0.0/include

clean:
	rm -f obj/*