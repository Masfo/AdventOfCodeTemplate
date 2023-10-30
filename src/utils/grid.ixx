module;


export module grid;

import std;
#if 0
export
{

	// DAY 8, 2022, walk lines all_of iota...


	// for_each_4way -> std::generator<Cell> ... co_yield
	// grid as a unordered_map

	const ivec2 north{0, -1};
	const ivec2 east{1, 0};
	const ivec2 south{0, 1};
	const ivec2 west{-1, 0};
	const ivec2 north_east{north + east};
	const ivec2 north_west{north + west};
	const ivec2 south_east{south + east};
	const ivec2 south_west{south + west};

	const std::vector<ivec2> directions_4_way{
		north,
		east,
		south,
		west,
	};

	const std::vector<ivec2> directions_4_diag{
		south_west,
		south_east,
		north_west,
		north_east,
	};

	const std::vector<ivec2> directions_8_way{
		north,
		east,
		south,
		west,

		north_east,
		north_west,
		south_east,
		south_west,
	};


	const std::vector<ivec2> hex_coords{
		north_east,
		east,
		south_east,
		south_west,
		west,
		north_west,
	};
	const std::unordered_map<std::string, ivec2> axial_coordinates{
		{"ne", ivec2(1, -1)},
		{"e", ivec2(1, 0)},
		{"se", ivec2(0, 1)},
		{"sw", ivec2(-1, 1)},
		{"w", ivec2(-1, 0)},
		{"nw", ivec2(0, -1)},
	};
}
#endif
