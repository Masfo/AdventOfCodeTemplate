module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 1454;
	
	constexpr uint32_t version = major * 100000 + minor * 10000 + build;
	constexpr uint64_t random_seed = 0x2aa0eec77c3a7c9a;
	
	constexpr char version_string[] = "v0.0.1454";
	constexpr char build_time_string[] = "2023-11-28 11:23:17";
	constexpr char phrase[] = "catacomb-recopy-amperage";
	constexpr char calver[] = "2023.48.1454";
	constexpr char uuid[] = "CE1E03E1-EA2F-4757-88F8-1A392E9E11CF";

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
