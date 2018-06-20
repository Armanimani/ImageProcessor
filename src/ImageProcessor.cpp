#include "ImageProcessor.hpp"

#include <fstream>
#include <iterator>
#include <vector>
#include <limits>

#include "UnionFind.hpp"

ImageProcessor::ImageProcessor(const std::string& path)
{
	readFile_(path);
}

void ImageProcessor::saveFile(const std::string& path)
{
	image_.write(path);
}

void ImageProcessor::loadFile(const std::string& path)
{
	readFile_(path);
}

void ImageProcessor::removeBackground(const ImageProcessor::Color &color, const double tolerance) noexcept
{
	UnionFind uf(width_ * height_ + 1);
	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			auto imgCol = image_[i][j];

			if ((imgCol.red - color.r) * (imgCol.red - color.r) + (imgCol.green - color.g) * (imgCol.green - color.g) + (imgCol.blue - color.b) * (imgCol.blue - color.b) <= tolerance * tolerance)
			{
				uf.connect(i * height_ + j, height_ * width_ + 1);
			}
		}
	}

	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			if (uf.isConnected(i * height_ + j, height_ * width_ + 1))
			{
				auto c = image_[i][j];
				c.alpha = 1.0;
				image_[i][j] = c;
			}
		}
	}
}

void ImageProcessor::fitImageToScreen() noexcept
{
	int minX = std::numeric_limits<int>::max();
	int minY = std::numeric_limits<int>::max();
	int maxX = std::numeric_limits<int>::min();
	int maxY = std::numeric_limits<int>::min();

	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			if (image_[i][j].alpha != 1)
			{
				if (i < minX)
					minX = i;
				if (i > maxX)
					maxX = i;
				if (j < minY)
					minY = j;
				if (j > maxY)
					maxY = j;
			}
		}
	}

	int newWidth = maxX - minX + 1;
	int newHeight = maxY - minY + 1;

	auto newImage = png::image<png::rgba_pixel>(newHeight, newWidth);

	for (auto i = 0; i != newWidth; i++)
	{
		for (auto j = 0; j != newHeight; j++)
		{
			newImage[i][j] = image_[i + minX][j + minY];
		}
	}

	image_ = newImage;
	width_ = newWidth;
	height_ = newHeight;
}

void ImageProcessor::readFile_(const std::string& path)
{
	image_ = png::image<png::rgba_pixel>(path);
	height_ = image_.get_height();
	width_ = image_.get_width();
}