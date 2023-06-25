
void day01();
void day02();
void day03();
void day04();
void day05();
void day06();
void day07();
void day08();
void day09();
void day10();
void day11();
void day12();
void day13();
void day14();
void day15();
void day16();
void day17();
void day18();
void day19();
void day20();
void day21();
void day22();
void day23();
void day24();
void day25();

#include "utils/standard.h"

#define ALL 1

int main()
{
	std::println("AOC 2022:\n\n");

	try
	{
		if constexpr (ALL == 1)
		{
			//
		}

		day01(); //

		if constexpr (ALL == 1)
		{
			// day02(); //
			// day03(); //
			// day04(); //
			// day05(); //
			// day06(); //
			// day07(); //
			//
			// day08(); //
			// day09(); //
			// day10(); //
			// day11(); //
			// day12(); //
			// day13(); //
			// day14(); //
			//
			// day15(); //
			// day16(); //
			// day17(); //
			// day18(); //
			// day19(); //
			// day20(); //
			// day21(); //
			//
			// day22(); //
			// day23(); //
			// day24(); //
			// day25(); //
		}
	}
	catch (const std::exception &e)
	{
		std::println("Exception: {}", e.what());
		return -1;
	}

	return 0;
}
