

export module aoc.grid;

import std;
import aoc.readfile;
import aoc.vec;
import aoc.debug;

export
{

	const ivec2 north{0, -1};
	const ivec2 east{1, 0};
	const ivec2 south{0, 1};
	const ivec2 west{-1, 0};
	const ivec2 north_east{north + east};
	const ivec2 south_east{south + east};
	const ivec2 south_west{south + west};
	const ivec2 north_west{north + west};

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
		north_east,
		east,
		south_east,
		south,
		south_west,
		west,
		north_west,
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

	// grid
	template<typename T = char>
	class grid
	{
	public:
		// [&](ivec2 pos, char c)
		using FunctionOp = const std::function<void(const ivec2, const T)>;

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
			calc_bounds();
		}

		void calc_bounds()
		{
			min_grid = MAX_IVEC2;
			max_grid = MIN_IVEC2;
			for (const auto &pos : std::views::keys(m_grid))
			{
				min_grid = min(min_grid, pos);
				max_grid = max(max_grid, pos);
			}
		}

		auto get_bounds() -> std::tuple<ivec2, ivec2> { return {min_grid, max_grid}; }

		auto getline(ivec2 start, ivec2 end) -> std::vector<T>
		{
			std::vector<T> gv;
			return gv;
		}

		void set_border(T c)
		{
			//
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

		void for_each_4way(const ivec2 pos, const FunctionOp &op) const
		{
			if (not is_valid(pos))
			{
				panic("Starting position {} is not valid", pos);
				return;
			}
			for (const ivec2 offset : directions_4_way)
			{
				if (auto v = at(pos + offset); v.has_value())
					op(pos + offset, *v);
			}
		}

		//
		void for_each_4way(const FunctionOp &op) const
		{
			for_each(
				[&](const ivec2 pos, T)
				{
					for_each_4way(pos,
								  [&](const ivec2 pos, T c)
								  {
									  if (auto v = at(pos); v.has_value())
										  op(pos, *v);
								  });
				});
		}

		void for_each_8way(const FunctionOp &op) const
		{
			for_each(
				[&](const ivec2 pos, T)
				{
					for_each_8way(pos,
								  [&](const ivec2 pos, T c)
								  {
									  if (auto v = at(pos); v.has_value())
										  op(pos, *v);
								  });
				});
		}

		void for_each_8way(const ivec2 pos, const FunctionOp &op) const
		{
			if (not is_valid(pos))
			{
				panic("Starting position {} is not valid", pos);
				return;
			}

			for (const ivec2 offset : directions_8_way)
			{
				if (auto v = at(pos + offset); v.has_value())
					op(pos + offset, *v);
			}
		}

		bool is_valid(ivec2 pos) const { return (pos >= min_grid) && (pos <= max_grid); }

		auto find(T to_find) const -> std::vector<ivec2>
		{
			std::vector<ivec2> points;

			for_each(
				[&](ivec2 pos, T c)
				{
					//
					if (c == to_find)
						points.push_back(pos);
				});

			return points;
		}

		bool contains(ivec2 pos) const { return m_grid.contains(pos); }

		std::optional<T> at(ivec2 pos) const
		{
			if (contains(pos))
				return m_grid.at(pos);
			return {};
		}

		void set(ivec2 pos, T value)
		{
			if (is_locked())
			{
				if (is_valid(pos))
					m_grid[pos] = value;
				else
				{

					panic("Trying to go out-of-bounds on locked grid. {}x{} = '{}'", pos.x(), pos.y(), value);
				}
			}
			else
			{
				m_grid[pos] = value;
			}
			calc_bounds();
		}

		void set_in_bounds(ivec2 pos, T value)
		{
			if (is_valid(pos))
				set(pos, value);
		}

		void unset(ivec2 pos) { m_grid.erase(pos); }

		void print()
		{
			dbgln("Bounds: {} - {}", min_bound(), max_bound());
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
						dbg(".");
					}
				}
				dbgln("");
			}
			dbgln("");
		}

		void lock(bool to_lock = true) { m_locked = to_lock; };

		bool is_locked() const { return m_locked; }

		ivec2 min_bound() const { return min_grid; }

		ivec2 max_bound() const { return max_grid; }

	private:
		ivec2 min_grid{MAX_IVEC2};
		ivec2 max_grid{MIN_IVEC2};

		std::unordered_map<ivec2, T> m_grid;
		bool                         m_locked{false};
	};

	// DAY 8, 2022, walk lines all_of iota...

	// for_each_4way -> std::generator<Cell> ... co_yield
	// grid as a unordered_map
}

#if 0


    auto no_elf_in_dirs = [&](ivec2 pos, ivec2 d1, ivec2 d2, ivec2 d3) { return (!elfs.contains(pos + d1) && !elfs.contains(pos + d2) && !elfs.contains(pos + d3)); };
    auto no_neighbours  = [&](ivec2 pos) { return std::ranges::all_of(directions_8_way, [&](const ivec2 &dir) { return !elfs.contains(pos + dir); }); };
	// 2022, day 23
#endif
