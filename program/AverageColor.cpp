#include <iostream>
#include <string>
#include <fstream>

#include "../src/ImageProcessor.hpp"

constexpr int SUCCESS = 0;
constexpr int INPUT_FAILURE = 1;
constexpr int OUTPUT_FAILURE = 2;

int main(int argc, char** argv)
{
	std::string inputFile;
	std::string outputFile;
	for (auto i = 0; i != argc; ++i)
	{
		std::string token {argv[i]};
		if (i != argc - 1)
		{
			if (token == "-input" )	
			{
				inputFile = std::string{argv[i + 1]};
			}
			else if (token == "-output")
			{
				outputFile = std::string{argv[i + 1]};
			}
		}
	}


	std::ifstream file(inputFile);
	if (!file.good())
	{
		std::cout << "***ERROR: File does not exist!  -> @" << inputFile << std::endl;
		return INPUT_FAILURE;
	}

	ImageProcessor ip(inputFile);
	ip.removeBackground(100);
	auto color = ip.calculate_averageNonTransparentColor();

	std::ofstream output(outputFile);
	if (!output.good())
	{
		std::cout << "***ERROR: File does not exist!  -> @" << outputFile << std::endl;
		return OUTPUT_FAILURE;
	}

	output << static_cast<int>(color[0]) << '\t' << static_cast<int>(color[1]) << '\t' << static_cast<int>(color[2]) << std::endl;

	return INPUT_FAILURE;
}