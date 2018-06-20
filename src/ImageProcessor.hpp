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
	};

	explicit ImageProcessor(const std::string& path);
	void saveFile(const std::string& path);
	void loadFile(const std::string& path);
	void fitImageToScreen() noexcept;
	void removeBackground(const ImageProcessor::Color& color, double tolerance = 0.0) noexcept;
private:
	double width_;
	double height_;
	png::image<png::rgba_pixel> image_;
	void readFile_(const std::string& path);
};