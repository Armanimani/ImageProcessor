#pragma once
#include <vector>
#include <array>
#include <algorithm>
#include <iostream>

class Screen2D
{
public:
	Screen2D(const int startX, const int endX, const int startY, const int endY, const int def = 0) 
		: startX_(startX), startY_(startY), endX_(endX), endY_(endY), lengthX_(endX - startX + 1), lengthY_(endY_ - startY_ + 1), length_(lengthX_ * lengthY_)
	{
		data_ = std::vector<int>(length_, def);
	}

	const int getStartX() const { return startX_; }
	const int getEndX() const { return endX_; }
	const int getStartY() const { return startY_; }
	const int getEndY() const { return endY_; }
	const int getLengthX() const {return lengthX_;}
	const int getLengthY() const {return lengthY_;}
	const int getLength() const {return length_;}

	const int getSize() const { return data_.size(); }

	std::array<int, 2> getPosition(const int index) const { return {startX_ + (index % lengthX_), startY_ + (index / lengthX_)}; }
	std::array<int, 2> getPositionRight(const int index) const { return {startX_ + (index % lengthX_) + 1, startY_ + (index / lengthX_)}; }
	std::array<int, 2> getPositionLeft(const int index) const { return {startX_ + (index % lengthX_) - 1, startY_ + (index / lengthX_)}; }
	std::array<int, 2> getPositionUp(const int index) const { return {startX_ + (index % lengthX_), startY_ + (index / lengthX_) + 1}; }
	std::array<int, 2> getPositionDown(const int index) const { return {startX_ + (index % lengthX_), startY_ + (index / lengthX_) - 1}; }

	const int getIndex(const int x, const int y) const { return lengthX_ * (y - startY_) + (x - startX_); }
	const int getIndexRight(const int x, const int y) const { return getIndex(x + 1, y); }
	const int getIndexLeft(const int x, const int y) const { return getIndex(x - 1, y); }
	const int getIndexUp(const int x, const int y) const { return getIndex(x, y + 1); }
	const int getIndexDown(const int x, const int y) const { return getIndex(x, y - 1); }

	const int getIndexRight(const int index) const { return getIndexRight(startX_ + (index % lengthX_), startY_ + (index / lengthX_)); }
	const int getIndexLeft(const int index) const { return getIndexLeft(startX_ + (index % lengthX_), startY_ + (index / lengthX_)); }
	const int getIndexUp(const int index) const { return getIndexUp(startX_ + (index % lengthX_), startY_ + (index / lengthX_)); }
	const int getIndexDown(const int index) const { return getIndexDown(startX_ + (index % lengthX_), startY_ + (index / lengthX_)); }

	const int& getValue(const int x, const int y) const { return data_[getIndex(x, y)]; }
	const int& getValueRight(const int x, const int y) const { return data_[getIndexRight(x, y)]; }
	const int& getValueLeft(const int x, const int y) const { return data_[getIndexLeft(x, y)]; }
	const int& getValueUp(const int x, const int y) const { return data_[getIndexUp(x, y)]; }
	const int& getValueDown(const int x, const int y) const { return data_[getValueDown(x, y)]; }

	const int& getValue(const int index) const { return data_[index]; }
	const int& getValueRight(const int index) const { return data_[getIndexRight(index)]; }
	const int& getValueLeft(const int index) const { return data_[getIndexLeft(index)]; }
	const int& getValueUp(const int index) const { return data_[getIndexUp(index)]; }
	const int& getValueDown(const int index) const { return data_[getIndexDown(index)]; }

	void setValue(const int x, const int y, const int value) { data_[getIndex(x, y)] = value; }
	void setValue(const int index, const int value) { data_[index] = value; }

	const int& maximumValue() const { return *std::max_element(data_.cbegin(), data_.cend()); }
	const int& minimumValue() const { return *std::min_element(data_.cbegin(), data_.cend()); }

protected:
	std::vector<int> data_{};
	int startX_{};
	int startY_{};
	int endX_{};
	int endY_{};
	int lengthX_{};
	int lengthY_{};
	int length_{};
};