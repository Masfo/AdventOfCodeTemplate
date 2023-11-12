module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 874;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0x2f6c683460ecb8c7;
	
	constexpr char version_string[] = "v0.0.874";
	constexpr char build_time_string[] = "2023-11-12 19:26:34";
	constexpr char phrase[] = "unwarlike-levers-cardiac";
	constexpr char calver[] = "2023.45.874";
	constexpr char uuid[] = "C8836DD9-A8A8-4198-A72B-1A0BDBDE87B1";

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
