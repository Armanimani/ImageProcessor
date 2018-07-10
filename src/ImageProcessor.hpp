#pragma once

#include <png++/png.hpp>

#include <string>
#include <memory>
#include <array>

#include "Screen2D.hpp"

class ImageProcessor
{
public:
	struct Color
	{
		int r;
		int g;
		int b;
		int a {255};
	};

	ImageProcessor(const std::string& path);
	void saveFile(const std::string& path);
	void loadFile(const std::string& path);
	void fitImageToScreen() noexcept;
	void removeBackground(double tolerance = 0.0, const ImageProcessor::Color& replacementColor = {255, 255, 255, 0}) noexcept;
	void divideAndSave(const std::vector<double>& divX, const std::vector<double>& divY, const std::string& path) const;
	void replaceColor(const ImageProcessor::Color& targetColor, double tolerance = 0.0, const ImageProcessor::Color& replacementColor = {255, 255, 255, 0}) noexcept;
	std::array<double, 3> calculate_averageNonTransparentColor() const noexcept;

private:
	double width_;
	double height_;
	png::image<png::rgba_pixel> image_;
	std::unique_ptr<Screen2D> screen_;

	void readFile_(const std::string& path);
	void checkDivision_(const std::vector<double>& div) const;
};