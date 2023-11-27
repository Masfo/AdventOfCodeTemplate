export module aoc.helpers;
import aoc.debug;
import std;
export
{
	// sort
	template<typename T>
	void sort(std::vector<T> & v)
	{
		std::ranges::sort(v);
	};

	template<typename T>
	void sort_greater(std::vector<T> & v)
	{
		std::ranges::sort(v, std::greater{});
	}

	// first n elements
	template<typename T>
	auto first(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.begin(), count, result.begin());
		return result;
	}

	// last n elements
	template<typename T>
	auto last(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.rbegin(), count, result.rbegin());
		return result;
	}

	// compare keys
	// example: const auto [min, max] = std::ranges::minmax_element(e, compare_keys);
	auto compare_keys         = [](const auto &e1, const auto &e2) { return e1.first < e2.first; };
	auto compare_keys_greater = [](const auto &e1, const auto &e2) { return e1.first > e2.first; };

	// compare values
	// example: const auto [min, max] = std::ranges::minmax_element(e, compare_values);
	auto compare_values         = [](const auto &e1, const auto &e2) { return e1.second < e2.second; };
	auto compare_values_greater = [](const auto &e1, const auto &e2) { return e1.second > e2.second; };

	// top
	auto top(const auto &container, size_t count = 1)
	{
		auto c = container;
		std::ranges::sort(c);
		return first(c, count);
	}

	// bottom
	auto bottom(const auto &container, size_t count = 1)
	{
		auto c = container;
		std::ranges::sort(c, std::greater{});
		return first(c, count);
	}
}
