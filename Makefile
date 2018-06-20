all:
	g++ test/main.cpp src/ImageProcessor.cpp -std=c++1z -I src/ `libpng-config --ldflags` -O3
run:
	./a.out

clean:
	rm *.out