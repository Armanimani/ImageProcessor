all:
	g++ test/main.cpp src/ImageProcessor.cpp -std=c++1z -I src/ `libpng-config --ldflags` -O3
run:
	./a.out

averageColor:
	g++ program/AverageColor.cpp src/ImageProcessor.cpp -std=c++1z -I src/ `libpng-config --ldflags` -O3

clean:
	rm *.out