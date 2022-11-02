CC=mpicxx #g++
#mpicxx
#-std=c++11
CFLAGS = -Iinc -W -Wall -pedantic #-ltiff
#TEST = -L/usr/local/opencv/gcc-4.9.2/3.0.0/lib -lopencv_core -lopencv_videoio
#LIBS = -I/usr/local/opencv/gcc-4.9.2/3.0.0/include -L/usr/local/opencv/gcc-4.9.2/3.0.0/lib -lopencv_core -lopencv_videoio #-lopencv_highgui -lopencv_imgproc
#-ltiff    -I/usr/local/opencv/gcc-4.9.2/3.0.0/include
#-I/usr/local/opencv/gcc-4.9.2/3.0.0/include -L/usr/local/opencv/gcc-4.9.2/3.0.0/lib
project: obj/main.o obj/image_manager.o
	$(CC) $(CFLAGS) -o project obj/main.o obj/image_manager.o

obj/main.o: src/main.cpp inc/image_manager.h
	$(CC) $(CFLAGS) -c -o obj/main.o src/main.cpp

obj/image_manager.o: src/image_manager.cpp inc/image_manager.h
	$(CC) $(CFLAGS) -c -o obj/image_manager.o src/image_manager.cpp

clean:
	rm -f obj/*