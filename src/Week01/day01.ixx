export module aoc.day01;
import std;
import aoc;

export void day01()
{
#if 0
	auto lines = read_lines("input\\day1.txt");
#else
	auto groups = read_lines("input\\day1test.txt");
#endif

	auto [id, p] = split_optional<char, std::string>("h := 10", " :=", 0, 1);

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", 0);
	aoc::println("	- Part 2: {}", 0);
	aoc::println("");
}
