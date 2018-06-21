#include "ImageProcessor.hpp"

#include <fstream>
#include <iterator>
#include <vector>
#include <limits>
#include <exception>

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


void ImageProcessor::removeBackground(double tolerance, const ImageProcessor::Color& replacementColor) noexcept
{
	auto c1 = image_[0][0];
	auto c2 = image_[width_ - 1][0];
	auto c3 = image_[0][height_ - 1];
	auto c4 = image_[width_ - 1][height_ - 1];

	Color backgroundColor { static_cast<int>(0.25 * (c1.red + c2.red + c3.red + c4.red)), static_cast<int>(0.25 * (c1.green + c2.green + c3.green + c4.green)), static_cast<int>(0.25 * (c1.blue + c2.blue + c3.blue + c4.blue))};

	screen_ = std::make_unique<Screen2D>(0, width_ - 1, 0, height_ - 1);
	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			auto imgCol = image_[i][j];

			if ((imgCol.red - backgroundColor.r) * (imgCol.red - backgroundColor.r) + (imgCol.green - backgroundColor.g) * (imgCol.green - backgroundColor.g) + (imgCol.blue - backgroundColor.b) * (imgCol.blue - backgroundColor.b) <= tolerance * tolerance)
			{
				screen_->setValue(i, j, 1);
			}
		}
	}

	UnionFind uf(width_ * height_ + 1);
	uf.connect(screen_->getIndex(0, 0), width_ * height_);
	uf.connect(screen_->getIndex(0, height_ - 1), width_ * height_);
	uf.connect(screen_->getIndex(width_ - 1, 0), width_ * height_);
	uf.connect(screen_->getIndex(width_ - 1, height_ - 1), width_ * height_);

	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			if (screen_->getValue(i, j) == 1)
			{
				if (i != width_ - 1 && screen_->getValue(i + 1, j) == 1)
				{
					uf.connect(screen_->getIndex(i, j), screen_->getIndex(i + 1, j));
				}
				if (j != height_ - 1 && screen_->getValue(i, j + 1) == 1)
				{
					uf.connect(screen_->getIndex(i, j), screen_->getIndex(i, j + 1));
				}
			}
		}
	}
	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			if (uf.isConnected(screen_->getIndex(i, j), height_ * width_))
			{
				auto color = image_[i][j];
				color.red = replacementColor.r;
				color.green = replacementColor.g;
				color.blue = replacementColor.b;
				color.alpha = replacementColor.a;
				image_[i][j] = color;
			}
		}
	}
}

void ImageProcessor::divideAndSave(const std::vector<double>& divX, const std::vector<double>& divY, const std::string& path) const
{
	checkDivision_(divX);
	checkDivision_(divY);

	std::vector<double> X = divX;
	std::vector<double> Y = divY;
	X.push_back(1.0);
	Y.push_back(1.0);

	for (auto i = 0, minX = 0; i != X.size(); ++i)
	{ 
		int maxX = static_cast<int>(X[i] * width_); 

		for (auto j = 0, minY = 0; j != Y.size(); ++j)
		{
			int maxY = static_cast<int>(Y[j] * height_); 

			int newWidth = maxX - minX + 1;
			int newHeight = maxY - minY + 1;

			auto newImage = png::image<png::rgba_pixel>(newHeight, newWidth);
			for (auto ii = 0; ii != newWidth; ii++)
			{
				for (auto jj = 0; jj != newHeight; jj++)
				{
					newImage[ii][jj] = image_[ii + minX][jj + minY];
				}
			}
			newImage.write(path + std::to_string(i + 1) + "x" + std::to_string(j + 1) + ".png");

			minY = maxY + 1;
		}

		minX = maxX + 1;
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
			if (image_[i][j].alpha != 0)
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

	int newWidth = maxX - minX;
	int newHeight = maxY - minY;

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

void ImageProcessor::replaceColor(const ImageProcessor::Color& targetColor, double tolerance, const ImageProcessor::Color& replacementColor) noexcept
{
	for (auto i = 0; i != width_; ++i)
	{
		for (auto j = 0; j != height_; ++j)
		{
			auto imgCol = image_[i][j];

			if ((imgCol.red - targetColor.r) * (imgCol.red - targetColor.r) + (imgCol.green - targetColor.g) * (imgCol.green - targetColor.g) + (imgCol.blue - targetColor.b) * (imgCol.blue - targetColor.b) <= tolerance * tolerance)
			{
				imgCol.red = replacementColor.r;
				imgCol.green = replacementColor.g;
				imgCol.blue = replacementColor.b;
				imgCol.alpha = replacementColor.a;
				image_[i][j] = imgCol;
			}
		}
	}
}

void ImageProcessor::readFile_(const std::string& path)
{
	image_ = png::image<png::rgba_pixel>(path);
	width_ = image_.get_height();
	height_ = image_.get_width();
}

void ImageProcessor::checkDivision_(const std::vector<double>& div) const
{
	for (auto i = div.cbegin(); i != div.cend(); ++i)
	{
		if (*i >= 1.0)
		{
			throw std::runtime_error("Divisions element should be less than 1");
		}
		if (i != div.cbegin())
		{
			if (*i <= *(i - 1))
			{
				throw std::runtime_error("Divisions element should be sorted");
			}
		}
	}
}