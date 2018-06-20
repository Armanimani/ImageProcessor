#pragma once

#include <array>
#include <algorithm>
#include <type_traits>
#include <vector>
#include <numeric>

class UnionFind
{
public:
	using size_type = std::size_t;
	explicit UnionFind(const size_type n);

	void connect(const size_type p, const size_type q) noexcept;
	const bool isConnected(const size_type p, const size_type q) noexcept;

	void addNode(const size_type n = 1);
	const size_type size() const noexcept;

	const int partitionCount() noexcept;
	const std::vector<size_type> getUniqueRoots();

protected:
	std::vector<size_type> data_{};
	std::vector<size_type> size_{};

	const size_type root(const size_type n) noexcept;
};

UnionFind::UnionFind(const size_type n)
{
	data_.resize(n);
	std::iota(data_.begin(), data_.end(), 0);
	size_.resize(n, 1);
}

void UnionFind::connect(const size_type p, const size_type q) noexcept
{
	auto root_p = root(p);
	auto root_q = root(q);
	if (size_[root_p] < size_[root_q])
	{
		data_[root_p] = data_[root_q];
		size_[root_q] += size_[root_p];
	}
	else
	{
		data_[root_q] = data_[root_p];
		size_[root_p] += size_[root_q];
	}
}

const bool UnionFind::isConnected(const size_type p, const size_type q) noexcept
{
	return (root(p) == root(q)) ? true : false;
}

void UnionFind::addNode(const size_type n)
{
	auto size = data_.size();
	for (std::remove_const_t<decltype(n)> i = 0; i != n; ++i)
	{
		data_.push_back(size + i);
	}
}

auto UnionFind::size() const noexcept -> const size_type
{
	return data_.size();
}

const int  UnionFind::partitionCount() noexcept
{
	int ret {0};
	for (size_type i = 0; i != data_.size(); ++i)
	{
		if (size_[i] != 1 && data_[i] == i) ret++;
	}
	return ret;
}
auto UnionFind::getUniqueRoots() -> const std::vector<size_type>
{
	auto size = partitionCount();
	std::vector<size_type> ret(data_.size(), -1);
	std::vector<int> roots;
	for (size_type i = 0; i != data_.size(); ++i)
	{
		if (!(size_[i] == 1 && root(i) == i))
		{
			int code;
			auto r = root(i);
			auto pos = std::find(roots.begin(), roots.end(), r);
			if ( pos != roots.end())
			{
				code = pos - roots.begin();
			}
			else
			{
				code = roots.size();
				roots.push_back(r);
			}
			ret[i] = code;
		}
	}
	return ret;
}

auto UnionFind::root(const size_type n) noexcept -> const size_type
{
	auto temp = n;
	while (data_[temp] != temp)
	{
		data_[temp] = data_[data_[temp]];
		temp = data_[temp];
	}
	return temp;
}