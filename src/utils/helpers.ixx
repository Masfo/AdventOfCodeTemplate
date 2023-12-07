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

	// compare keys
	// example: const auto [min, max] = std::ranges::minmax_element(map, compare_keys);
	auto compare_keys         = [](const auto &e1, const auto &e2) { return e1.first < e2.first; };
	auto compare_keys_greater = [](const auto &e1, const auto &e2) { return e1.first > e2.first; };

	// compare values
	// example: const auto [min, max] = std::ranges::minmax_element(map, compare_values);
	auto compare_values         = [](const auto &e1, const auto &e2) { return e1.second < e2.second; };
	auto compare_values_greater = [](const auto &e1, const auto &e2) { return e1.second > e2.second; };

	// ###########################

	template<typename T>
	concept ContainerResize = requires(T a) {
		a.size();
		a.resize(0);
		a.begin();
		a.rbegin();
	};

	// take n elements
	template<ContainerResize T>
	auto take(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		if (count == container.size())
			return container;

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.begin(), count, result.begin());
		return result;
	}

	// last n elements
	template<ContainerResize T>
	auto last(const T &container, size_t count)
	{
		assert_msg(count <= container.size(), "Count is larger than the container");

		if (count == container.size())
			return container;

		T result{};
		result.resize(count);
		std::ranges::copy_n(container.rbegin(), count, result.rbegin());
		return result;
	}

	// top
	auto top(const auto &container, size_t count)
	{
		assert_msg(container.size() <= count, "Container not big enough");
		auto c = container;
		std::ranges::sort(c);
		return take(c, count);
	}

	auto top(const auto &container) { return top(container, 1)[0]; }

	// bottom
	auto bottom(const auto &container, size_t count)
	{
		assert_msg(container.size() <= count, "Container not big enough");

		auto c = top(container, count);
		return last(c, count);
	}

	auto bottom(const auto &container) { return bottom(container, 1)[0]; }

	// move index
	template<typename T>
	void move_index(T & v, size_t oldIndex, size_t newIndex)
	{
		if (oldIndex > newIndex)
			std::rotate(v.rend() - oldIndex - 1, v.rend() - oldIndex, v.rend() - newIndex);
		else
			std::rotate(v.begin() + oldIndex, v.begin() + oldIndex + 1, v.begin() + newIndex + 1);
	}

	template<typename T, typename U>
	size_t index_of(T & v, U find)
	{
		return std::ranges::distance(v.begin(), std::ranges::find(v, find));
	}
}
