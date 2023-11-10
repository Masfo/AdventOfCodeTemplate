export module aoc.day01;
import std;
import aoc;

export void day01()
{
	answer a;
#if 0
	auto lines = read_lines("input\\day1.txt");
#else
	auto groups = read_lines("input\\day1test.txt");
#endif

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", a.part1);
	aoc::println("	- Part 2: {}", a.part2);
	aoc::println("");
}
