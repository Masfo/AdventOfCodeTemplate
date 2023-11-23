export module aoc.helpers;

export
{
	// compare keys
	auto key_less    = [](const auto &e1, const auto &e2) { return e1.first < e2.first; };
	auto key_greater = [](const auto &e1, const auto &e2) { return e1.first > e2.first; };

	// compare values
	auto value_less    = [](const auto &e1, const auto &e2) { return e1.second < e2.second; };
	auto value_greater = [](const auto &e1, const auto &e2) { return e1.second > e2.second; };
}
