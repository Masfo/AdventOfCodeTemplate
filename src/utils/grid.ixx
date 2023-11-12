

export module aoc.grid;

import std;
import aoc.readfile;
import aoc.vec;
import aoc.debug;

export
{
	template<typename T>
	struct GridValue
	{
		T     value{};
		ivec2 pos;
	};

	template<typename T = char>
	class grid
	{
	public:
		using FunctionOp     = std::function<void(const ivec2, T)>;
		using FunctionOpThis = std::function<void(grid<T> &, const ivec2, T)>;

		void read(std::string_view filename)
		{
			auto  lines = read_lines(filename);
			ivec2 pos;
			for (const auto &row : lines)
			{
				pos[0] = 0;
				for (const auto &c : row)
				{
					m_grid[pos] = c;
					pos[0]++;
				}
				pos[1]++;
			}
			const auto [mmin, mmax] = bounds();
			min_grid                = mmin;
			max_grid                = mmax;
		}

		auto bounds() -> std::tuple<ivec2, ivec2>
		{
			ivec2 mmin{MAX_IVEC2}, mmax{MIN_IVEC2};
			for (const auto &pos : std::views::keys(m_grid))
			{
				mmin = min(mmin, pos);
				mmax = max(mmax, pos);
			}
			return {mmin, mmax};
		}

		auto getline(ivec2 start, ivec2 end) -> std::vector<GridValue<T>>
		{
			std::vector<GridValue<T>> gv;
			return gv;
		}

		void setline(ivec2 v1, ivec2 v2, T c)
		{
			ivec2 delta;
			if (v2[0] - v1[0] != 0)
				delta[0] = v2[0] - v1[0] > 0 ? 1 : -1;
			if (v2[1] - v1[1] != 0)
				delta[1] = v2[1] - v1[1] > 0 ? 1 : -1;

			set(v1, c);

			while (v1.x() != v2.x() || v1.y() != v2.y())
			{
				v1 += delta;
				set(v1, c);
			}
		}

		void for_each(const FunctionOp &op) const
		{
			for (auto y = min_grid.y(); y <= max_grid.y(); ++y)
			{
				for (auto x = min_grid.x(); x <= max_grid.x(); ++x)
				{
					if (auto v = at(ivec2{x, y}); v.has_value())
					{
						op(ivec2{x, y}, *v);
					}
				}
			}
		}

		void for_each(const FunctionOpThis &op)
		{
			for (auto y = min_grid.y(); y <= max_grid.y(); ++y)
			{
				for (auto x = min_grid.x(); x <= max_grid.x(); ++x)
				{
					if (auto v = at(ivec2{x, y}); v.has_value())
					{
						op(*this, ivec2{x, y}, *v);
					}
				}
			}
		}

		bool is_valid(ivec2 pos) const { return (pos <= min_grid) && (pos >= max_grid); }

		auto find(T c) const -> std::vector<ivec2>
		{
			std::vector<ivec2> points;

			return points;
		}

		bool contains(ivec2 pos) const { return m_grid.contains(pos); }

		std::optional<T> at(ivec2 pos) const
		{
			if (contains(pos))
				return m_grid.at(pos);
			return {};
		}

		void set(ivec2 pos, T value) { m_grid[pos] = value; }

		void unset(ivec2 pos) { m_grid.erase(pos); }

		void print()
		{
			for (auto y = min_grid.y(); y <= max_grid.y(); ++y)
			{
				for (auto x = min_grid.x(); x <= max_grid.x(); ++x)
				{
					if (auto v = at(ivec2{x, y}); v.has_value())
					{
						dbg("{}", *v);
					}
					else
					{
						dbg(" ");
					}
				}
				dbgln("");
			}
			dbgln("");
		}

	private:
		ivec2 min_grid{MAX_IVEC2};
		ivec2 max_grid{MIN_IVEC2};

		std::unordered_map<ivec2, T> m_grid;
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


    auto no_elf_in_dirs = [&](ivec2 pos, ivec2 d1, ivec2 d2, ivec2 d3) { return (!elfs.contains(pos + d1) && !elfs.contains(pos + d2) && !elfs.contains(pos + d3)); };
    auto no_neighbours  = [&](ivec2 pos) { return std::ranges::all_of(directions_8_way, [&](const ivec2 &dir) { return !elfs.contains(pos + dir); }); };
	// 2022, day 23
#endif
