export module aoc.day01;
import std;
import aoc;
import aoc.vec;

export void day01()
{
#if 0
	auto lines = read_lines("input\\day1.txt");
#else
	auto lines = read_lines("input\\day1test.txt");
#endif

	ivec4 a{1, 2, 3, 4, 5};
	ivec4 b{a};

	dbgln("{} {}", a, b);

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", 0);
	aoc::println("	- Part 2: {}", 0);
	aoc::println("");
}
