export module aoc.day01;
import std;
import aoc;

export void day01()

{
	answer a;
#if 0
	auto lines = read_lines("input\\day1.txt");
#else
	//auto lines = read_lines("input\\day1test.txt");
	//auto lines = read_all_lines("input\\day1test.txt");
	//auto lines = read_lines_as<i64>("input\\day1test.txt");
	auto lines = read_all_lines_as<i64>("input\\day1test.txt");

#endif

	// auto v    = std::vector{1, 2, 3, 1, 2, 3, 3, 3, 1, 2, 3};
	// auto fun  = std::ranges::less{};
	// auto view = v | std::views::chunk_by(fun);

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", a.part1);
	aoc::println("	- Part 2: {}", a.part2);
	aoc::println("");
}
