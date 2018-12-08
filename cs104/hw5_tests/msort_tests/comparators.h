#include <functional>
#include <string>
#include <vector>

struct intCompareLess
{
	bool operator()(const int lhs, const int rhs) {
		return lhs < rhs;
	}
};

struct intCompareGreater
{
	bool operator()(const int lhs, const int rhs) {
		return lhs > rhs;
	}
};

struct stringCompareLess
{
	bool operator()(const std::string lhs, const std::string rhs) {
		return lhs < rhs;
	}
};

struct stringCompareGreater
{
	bool operator()(const std::string lhs, const std::string rhs) {
		return lhs > rhs;
	}
};

template<typename T1, typename T2>
struct PairFirstLess
{
	bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs)
	{
		return lhs.first < rhs.first;
	}
};

template<typename T1, typename T2>
struct PairSecondLess
{
	bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs)
	{
		return lhs.second < rhs.second;
	}
};

template<typename T1, typename T2>
struct PairFirstGreater
{
	bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs)
	{
		return lhs.first > rhs.first;
	}
};

template<typename T1, typename T2>
struct PairSecondGreater
{
	bool operator()(const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs)
	{
		return lhs.second > rhs.second;
	}
};