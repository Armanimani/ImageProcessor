#include <iostream>

#include "../src/ImageProcessor.hpp"

int main()
{
	ImageProcessor ip("test/sample.png");
	ip.removeBackground({255, 255, 255}, 20);
	ip.fitImageToScreen();
	ip.saveFile("test/output_cropped.png");

}