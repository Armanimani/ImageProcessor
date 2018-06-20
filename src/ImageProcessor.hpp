#pragma once

#include <png++/png.hpp>

#include <string>

class ImageProcessor
{
public:
	struct Color
	{
		int r;
		int g;
		int b;
		int a {0};
	};

	ImageProcessor(const std::string& path);
	void saveFile(const std::string& path);
	void loadFile(const std::string& path);
	void fitImageToScreen() noexcept;
	void removeBackground(const ImageProcessor::Color& backgroundColor, double tolerance = 0.0, const ImageProcessor::Color replacementColor = {0, 0, 0, 1}) noexcept;
	void removeBackground(double tolerance = 0.0, const ImageProcessor::Color& replacementColor = {0, 0, 0, 1}) noexcept;

	void cropAndSave(const std::vector<double>& divX, const std::vector<double>& divY, const std::string& path) const;
private:
	double width_;
	double height_;
	png::image<png::rgba_pixel> image_;
	void readFile_(const std::string& path);
	void removeBackground_impl_(const ImageProcessor::Color& backgroundColor, double tolerance, const ImageProcessor::Color& replacementColor) noexcept;
	void checkDivision_(const std::vector<double>& div) const;
};