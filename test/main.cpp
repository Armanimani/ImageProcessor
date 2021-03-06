#include <iostream>

#include "ImageProcessor.hpp"

void test_removeBackground(const std::string& input)
{
	std::cout << "testing: removing background..." << std::flush;
	ImageProcessor ip(input);
	ip.removeBackground(100);
	ip.saveFile("output/backgroundRemoved.png");
	std::cout << "done!" << std::endl;
}

void test_removeBackground2(const std::string& input)
{
	std::cout << "testing: removing background2..." << std::flush;
	ImageProcessor ip(input);
	ip.removeBackground(100, {255, 0, 0, 255});
	ip.saveFile("output/backgroundRemoved2.png");
	std::cout << "done!" << std::endl;
}

void test_fitToScreen(const std::string& input)
{
	std::cout << "testing: removing background and fitting to screen..." << std::flush;
	ImageProcessor ip(input);
	ip.removeBackground(100);
	ip.fitImageToScreen();
	ip.saveFile("output/fitToScreen.png");
	std::cout << "done!" << std::endl;
}

void test_tolerance(const std::string& input)
{
	std::cout << "testing: tolerance test..." << std::flush;
	std::string outputPath { "output/tolerance_" };
	for (auto tol = 0; tol != 200; tol += 5)
	{
		ImageProcessor ip(input);
		ip.removeBackground(tol, {87, 0, 255, 255});
		ip.saveFile(outputPath + std::to_string(tol) +".png");
	}
	std::cout << "done!" << std::endl;
}

void test_dividing1(const std::string& input)
{
	std::cout << "testing: dividing..." << std::flush;
	ImageProcessor ip(input);
	ip.removeBackground(100);
	ip.fitImageToScreen();
	ip.divideAndSave({0.5}, {0.50}, "output/divide1_");
	std::cout << "done!" << std::endl;
}

void test_dividing2(const std::string& input)
{
	std::cout << "testing: dividing2..." << std::flush;
	ImageProcessor ip(input);
	ip.removeBackground(100);
	ip.fitImageToScreen();
	ip.divideAndSave({0.5, 0.75}, {}, "output/divide2_");
	std::cout << "done!" << std::endl;
}

int main()
{
	std::string input { "input/sample.png" };

	test_removeBackground(input);
	test_removeBackground2(input);
	test_fitToScreen(input);
	test_tolerance(input);
	test_dividing1(input);
	test_dividing2(input);
}