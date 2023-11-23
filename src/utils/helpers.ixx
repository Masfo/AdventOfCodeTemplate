export module aoc.helpers;

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
}
