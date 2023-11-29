export module aoc.day02;
import std;
import aoc;

export void day02()
{
#if 0
    auto filename = "input\\day2.txt";
#else
	auto filename = "input\\day2test.txt";
#endif
	// auto lines = read_lines(filename);
	// auto lines = read_lines_exact(filename);
	// auto lines = read_all_lines(filename);
	auto lines = read_lines_as<i64>(filename);
	// auto lines = read_all_lines_as<i64>(filename);
	// auto lines = read_csv(filename);

	for (const auto &i : lines)
	{
		//
	}

	aoc::println("Day 02 :");
	aoc::println("	- Part 1: {}", 0);
	aoc::println("	- Part 2: {}", 0);
	aoc::println("");
}
