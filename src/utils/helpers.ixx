export module aoc.helpers;
import std;
export
{
	// compare keys
	// example: const auto [min, max] = std::ranges::minmax_element(e, key_less);
	auto key_less    = [](const auto &e1, const auto &e2) { return e1.first < e2.first; };
	auto key_greater = [](const auto &e1, const auto &e2) { return e1.first > e2.first; };

	// compare values
	// example: const auto [min, max] = std::ranges::minmax_element(e, value_less);
	auto value_less    = [](const auto &e1, const auto &e2) { return e1.second < e2.second; };
	auto value_greater = [](const auto &e1, const auto &e2) { return e1.second > e2.second; };

	// top
	auto top(const auto &container, size_t count = 1)
	{
		auto c = container;
		std::ranges::sort(c);
		decltype(c) result{};
		result.resize(count);
		std::ranges::copy_n(c.begin(), count, result.begin());
		return result;
	}

	// bottom
	auto bottom(const auto &container, size_t count = 1)
	{
		auto c = container;
		std::ranges::sort(c, std::greater{});
		decltype(c) result{};
		result.resize(count);
		std::ranges::copy_n(c.begin(), count, result.begin());
		return result;
	}
}
