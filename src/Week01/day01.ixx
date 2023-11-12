export module aoc.day01;
import std;
import aoc;

export void day01()

{
	answer a;
#if 0
	auto lines = read_lines("input\\day1.txt");
#else
	auto lines = read_lines("input\\day1test.txt");
#endif

	grid g;
	g.read("input\\day1test.txt");

	g.print();

	g.for_each(
		[&g](const ivec2 pos, char c)
		{
			//
			// self.set(pos, '$');
		});

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", a.part1);
	aoc::println("	- Part 2: {}", a.part2);
	aoc::println("");
}
