export module aoc.day01;
import std;
import aoc;

export void day01()
{
	auto lines = read_lines("input\\day1.txt");

	for (const auto &column : std::views::iota(0, 32))
	{
		for (const auto &row : std::views::iota(0, 96) | std::views::stride(32))
		{
			int num = column + row;
			dbg("{0:>03d} {0:#04x} {1:2c} ", num, num > 32 && num < 128 ? num : ' ');
		}
		dbgln();
	}

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", 0);
	aoc::println("	- Part 2: {}", 0);
	aoc::println("");
}
