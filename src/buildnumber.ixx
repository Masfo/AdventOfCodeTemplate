module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 288;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0xb49dbc1f27b39034;
	
	constexpr char version_string[] = "v0.0.288";
	constexpr char build_time_string[] = "2023-11-01 00:32:26";
	constexpr char phrase[] = "duty-whinny-unmade";
	constexpr char calver[] = "2023.44.288";
	constexpr char uuid[] = "661AB842-6C1F-4AA8-8D68-F40283588FEC";

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
