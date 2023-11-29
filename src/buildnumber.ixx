module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 1502;
	
	constexpr uint32_t version = major * 100000 + minor * 10000 + build;
	constexpr uint64_t random_seed = 0xfeba7735e6bfbe7e;
	
	constexpr char version_string[] = "v0.0.1502";
	constexpr char build_time_string[] = "2023-11-29 12:11:03";
	constexpr char phrase[] = "hardhat-feminine-entitle";
	constexpr char calver[] = "2023.48.1502";
	constexpr char uuid[] = "CB21ACE4-79F4-436D-B7B5-79833BAEF9B6";

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
