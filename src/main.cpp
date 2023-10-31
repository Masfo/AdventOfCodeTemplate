import std;
import aoc.debug;
import aoc.days;


#define ALL 0
namespace fs = std::filesystem;

void write_to_file(fs::path directory, int day, std::string_view content)
{
	std::string file     = std::format("day{:02d}.ixx", day);
	fs::path    filepath = fs::current_path() / directory / file;

	if (day == -1)
		filepath = fs::current_path() / directory;

	if (fs::exists(filepath))
	{
		println("Could not write to file '{}'", file);
		return;
	}
	std::ofstream output;
	output.open(filepath.c_str());
	output << content;
	output.close();
}

void generate_days()
{
	if (fs::exists("Week01"))
	{
		aoc::println("Week directory exists. Remove");
		return;
	}
	fs::create_directory("Week01");
	fs::create_directory("Week02");
	fs::create_directory("Week03");
	fs::create_directory("Week04");

	std::string days;
	days.append("export module aoc.days;\n\n");
	for (int i = 1; i <= 25; ++i)
		days.append(std::format("export import aoc.day{:02d};\n", i));
	days.append("\n");

	write_to_file("days.ixx", -1, days);

	auto gen_day = [](int day) -> std::string
	{
		aoc::println("Gen day: {}", day);
		std::string temp;
		temp.append(std::format("export module aoc.day{:02d};\n", day));
		temp.append("import std;\n");
		temp.append("import aoc;\n");
		temp.append("\n");
		temp.append(std::format("export void day{:02d}()\n", day));
		temp.append("{\n");
		temp.append(std::format("    auto lines = read_lines(\"input\\\\day{}.txt\");\n", day));
		temp.append("\n");
		temp.append("\n");
		temp.append(std::format("    aoc::println(\"Day {:02d} :\");\n", day));
		temp.append("    aoc::println(\"\t- Part 1: {}\", 0);\n");
		temp.append("    aoc::println(\"\t- Part 2: {}\", 0);\n");
		temp.append("    aoc::println();\n");
		temp.append("}\n");
		return temp;
	};

	int day = 1;
	for ([[maybe_unused]] const int week01 : std::views::iota(0, 7))
	{
		write_to_file("Week01", day, gen_day(day));
		day++;
	}

	for ([[maybe_unused]] const int week02 : std::views::iota(8, 15))
	{
		write_to_file("Week02", day, gen_day(day));
		day++;
	}

	for ([[maybe_unused]] const int week03 : std::views::iota(15, 22))
	{
		write_to_file("Week03", day, gen_day(day));
		day++;
	}

	for ([[maybe_unused]] const int week04 : std::views::iota(23, 27))
	{
		write_to_file("Week04", day, gen_day(day));
		day++;
	}
}

int main()
{
	// generate_days();
	std::println("AOC 2023:\n\n");

	// pass command line option for test/real input
	// if not set use ifdef the usual day02.txt
	// if set override

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
		aoc::println("Exception: {}", e.what());
		return -1;
	}

	return 0;
}
