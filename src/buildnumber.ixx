module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 1257;
	
	constexpr uint32_t version = major * 100000 + minor * 10000 + build;
	constexpr uint64_t random_seed = 0xf03cfb9b7fa90e4e;
	
	constexpr char version_string[] = "v0.0.1257";
	constexpr char build_time_string[] = "2023-11-22 14:07:54";
	constexpr char phrase[] = "tiptoeing-stopwatch-useable";
	constexpr char calver[] = "2023.47.1257";
	constexpr char uuid[] = "DEC6986F-F673-4038-8BD1-CDE04249117C";

	// Copy paste to import to your project
	/*
		constexpr auto major = aoc::major;
		constexpr auto minor = aoc::minor;
		constexpr auto build = aoc::build;
		constexpr auto version = aoc::version;
		constexpr auto random_seed = aoc::random_seed;
			
		constexpr auto version_string = aoc::version_string;
		constexpr auto build_time_string = aoc::build_time_string;
		constexpr auto phrase = aoc::phrase;
		constexpr auto calver = aoc::calver;
		constexpr auto uuid = aoc::uuid;
	*/
}
