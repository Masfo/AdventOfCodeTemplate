module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 36;
	
	constexpr uint32_t version = major * 1000 + minor * 100 + build;
	constexpr uint64_t random_seed = 0x5f0d65f671d3d703;
	
	constexpr char version_string[] = "v0.0.36";
	constexpr char build_time_string[] = "2023-10-30 19:42:20";
	constexpr char phrase[] = "supermom-expansive-schedule";
	constexpr char calver[] = "2023.44.36";
	constexpr char uuid[] = "CFA86AD9-2443-4957-9CEF-FF6FCC95C955";

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
