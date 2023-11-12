module;
#include <cstdint>

export module aoc;
export namespace aoc
{
	 // You can modify major and minor
	constexpr uint32_t major = 0;
	constexpr uint32_t minor = 0;

	 // Do not modify these
	constexpr uint32_t build = 936;
	
	constexpr uint32_t version = major * 10000 + minor * 1000 + build;
	constexpr uint64_t random_seed = 0x3d5c94f413ed3261;
	
	constexpr char version_string[] = "v0.0.936";
	constexpr char build_time_string[] = "2023-11-12 21:31:33";
	constexpr char phrase[] = "grant-alphabet-altitude";
	constexpr char calver[] = "2023.45.936";
	constexpr char uuid[] = "0CD5B8CF-C3D3-4533-9BA7-A8319F446CF1";

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
