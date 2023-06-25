module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 4;
	
	constexpr uint32_t version = major * 100 + minor * 10 + build;
	constexpr uint64_t random_seed = 0x7fcbe450d0b1102f;
	
	constexpr char version_string[] = "v0.0.4";
	constexpr char build_time_string[] = "2023-06-25 18:32:09";
	constexpr char phrase[] = "skimmer-gumdrop-petty";
	constexpr char calver[] = "2023.25.4";
	constexpr char uuid[] = "E6981D8B-8331-467A-82EE-001A6C76D88D";

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
