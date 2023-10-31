import std;
import aoc;

auto filter   = [](char x, char y) { return [x, y](char a, char b) { return not(x == a or y == b); }; };
auto newline  = [](char, char) { return [](char x, char y) { return (x == '\n' and y != '\n'); }; };
auto newline2 = [](char, char) { return [](char x, char y) { return not(x == '\n' and y == '\n'); }; };

auto newline3 = [](char x, char y) { return not(x == '\n' and y == '\n'); };


auto filter_nl = [](char c) { return c != '\n'; };
auto chunk_nl  = [](char c, char) { return c != '\n'; };


auto chunk_by_double_newline = std::views::chunk_by(newline3) | std::ranges::to<std::vector<std::string>>();

void day01()
{
	auto lines = read_lines("input\\day3.txt");

	// 	auto g1 = lines | chunk_by_double_newline;
	// 	for (const auto &line : g1)
	// 	{
	// 		auto g2 = line | std::views::split('\n') | std::views::transform([](auto str) { return to_i64(str); }) |
	// 				  std::ranges::to<std::vector<i64>>();
	//
	// 		auto x = 0;
	// 	}

	const std::vector v = {1, 2, 3, 4, 5, 6};

	for (const auto &chunk : v | std::views::chunk(3))
	{
		for (const auto &c : chunk)
			dbg("{}", c);
		dbgln("/");
	}

	u64 sum = 0;
	std::vector<std::string> for (const auto &group : std::views::all(lines) | std::views::chunk(3))
	{
		std::string s;
		for (const auto &g : group)
			for (const auto &c : g)
				s.push_back(c);


		auto i        = string_intersection(s.substr(0, s.size() / 2), s.substr(s.size() / 2));
		u64  priority = between(i[0], 'a', 'z') ? i[0] - 96 : i[0] - 38;
		sum += priority;
		dbgln("line: {} = {}, {}", i, priority, sum);
	}

	for (const std::string &line : lines | std::views::chunk(3) | std::views::join)
	{
		auto i        = string_intersection(line.substr(0, line.size() / 2), line.substr(line.size() / 2));
		u64  priority = between(i[0], 'a', 'z') ? i[0] - 96 : i[0] - 38;
		sum += priority;
		dbgln("line: {} = {}, {}", i, priority, sum);
	}


	std::println("Day 01:");
	std::println("\t- Part 1: {}", 0);
	std::println("\t- Part 2: {}", 0);
	std::println("");
}
