module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 1057;
	
	constexpr uint32_t version = major * 100000 + minor * 10000 + build;
	constexpr uint64_t random_seed = 0xa4bbb99a7757e21e;
	
	constexpr char version_string[] = "v0.0.1057";
	constexpr char build_time_string[] = "2023-11-14 20:34:30";
	constexpr char phrase[] = "emergency-sherry-cannon";
	constexpr char calver[] = "2023.46.1057";
	constexpr char uuid[] = "30DE058B-FB2A-492F-B362-A06C0ED90EEE";

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
