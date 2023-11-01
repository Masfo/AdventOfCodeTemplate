

export module aoc.grid;

import std;
import aoc.vec;

export
{

	class grid
	{
	public:
	private:
		std::unordered_map<ivec2, char> m_data;
	};

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

#if 0
auto read_simple_grid(std::string_view filename, std::string_view interesting) -> std::unordered_set<ivec2>
{
    auto lines = read_all_lines(filename);

    std::unordered_set<ivec2> simple;
    ivec2                     pos;
    for (const auto &line : lines)
    {
        pos.x = 0;
        for (const auto &c : line)
        {
            if (interesting.contains(c))
                simple.insert(pos);
            pos.x++;
        }
        pos.y++;
    }
    return simple;
}

auto simple_grid_bounds(const std::unordered_set<ivec2> &grid) -> std::tuple<i64, i64, i64, i64>
{
    i64 minx{MAX_I64}, miny{MAX_I64}, maxx{0}, maxy{0};
    for (const auto &g : grid)
    {
        minx = std::min(minx, g.x);
        maxx = std::max(maxx, g.x);

        miny = std::min(miny, g.y);
        maxy = std::max(maxy, g.y);
    }
    return {minx, miny, maxx + 1, maxy + 1};
}

auto simple_grid_area(const std::unordered_set<ivec2> &grid) -> std::tuple<i64, i64, i64>
{
    const auto [minx, miny, maxx, maxy] = simple_grid_bounds(grid);
    const i64 width                     = std::abs(minx - maxx);
    const i64 height                    = std::abs(miny - maxy);

    return {width * height, width, height};
}

void simple_grid_print(const std::unordered_set<ivec2> &grid)
{
    const auto [minx, miny, maxx, maxy] = simple_grid_bounds(grid);
    for (int y = miny; y <= maxy; ++y)
    {
        for (int x = minx; x <= maxx; ++x)
        {
            if (grid.contains({x, y}))
                print("#");
            else
                print(".");
        }
        println();
    }
    println();
}

    auto no_elf_in_dirs = [&](ivec2 pos, ivec2 d1, ivec2 d2, ivec2 d3) { return (!elfs.contains(pos + d1) && !elfs.contains(pos + d2) && !elfs.contains(pos + d3)); };
    auto no_neighbours  = [&](ivec2 pos) { return std::ranges::all_of(directions_8_way, [&](const ivec2 &dir) { return !elfs.contains(pos + dir); }); };
	// 2022, day 23
#endif
