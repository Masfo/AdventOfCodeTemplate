export module aoc.day01;
import std;
import aoc;

export void day01()
{
#if 0
	auto lines = read_all_lines("input\\day1.txt");
#else
	auto lines = read_all_lines("input\\day1test.txt");
#endif

	std::string a("  123456x  ");
	dbgln("'{}' - '{}'", a, a | trim_view | to_string);

	std::string_view x  = trim(a);
	std::string_view x2 = trim("abc");

	std::vector<i64> elves;

	std::ranges::for_each(lines | chunk_by_emptyline,
						  [&](const auto &group)
						  {
							  i64 sum = 0;
							  for (const auto &i : group | transform_to_number<>)
								  sum += i ? *i : 0;

							  elves.push_back(sum);
						  });

	std::ranges::sort(elves, std::greater{});
	auto part1 = elves[0];
	auto part2 = elves[0] + elves[1] + elves[2];

	aoc::println("Day 01 :");
	aoc::println("	- Part 1: {}", part1);
	aoc::println("	- Part 2: {}", part2);
	aoc::println("");
}
