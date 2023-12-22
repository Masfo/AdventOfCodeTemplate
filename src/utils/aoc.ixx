module;

export module aoc;

export import aoc.debug;
export import aoc.vec;
export import aoc.math;
export import aoc.cube;
export import aoc.polygon;
export import aoc.readfile;

export import aoc.stringhelper;
export import aoc.stringsplit;

export import aoc.helpers;
export import aoc.types;
export import aoc.tree;
export import aoc.grid;
export import aoc.grid2d;
export import aoc.walker;

export import aoc.sprite;
export import aoc.ppm;

import aoc.debug;

export namespace aoc
{

	void print_answer(int day, auto part1, auto part2)
	{
		aoc::println("Day {:02}:", day);
		aoc::println("	- Part 1: {}", part1);
		aoc::println("	- Part 2: {}", part2);
		aoc::println("");
	}
} // namespace aoc
