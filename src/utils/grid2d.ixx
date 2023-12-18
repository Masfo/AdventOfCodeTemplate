export module aoc.grid2d;

import std;
import aoc.types;
import aoc.vec;
import aoc.debug;
import aoc.readfile;
import aoc.stringsplit;
import aoc.grid;

// grid2d
export
{
	/* TODO:
	 *		Static and dynamic, for moving objects
	 *			- mark during loading, what are dynamic elements
	 *			- move only dynamic elements
	 *		Maybe layers

	struct grid2d;

	auto match = [](grid2d &grid, ivec2 pos, char c)
	{
		//
		switch (c)
		{					// Layer
			case '.':       // ↓
			case '#': grid.set(0, pos, c); break;
			case 'O': grid.set(1, pos, c); break;
			default: break;
		}
	};

	grid2d g("filename", match);
	 */

	struct grid2d final
	{
		using Type      = char;
		using VecType   = std::vector<Type>;
		using hash_type = size_t;

		grid2d() = default;

		grid2d(i64 w, i64 h, Type f = '.')
		{
			width  = w;
			height = h;
			data.resize(height);
			for (auto &d : data)
				d.resize(width);
			recalc_size();

			fill(f);
		}

		grid2d(std::string_view filename) { read(filename); }

		// from lines
		void from_lines(std::string_view input, std::string_view delim = "\n") noexcept { from_lines(split(input, delim)); }

		void from_lines(const std::vector<std::string> &lines) noexcept
		{
			reset();

			width  = lines[0].size();
			height = lines.size();

			std::vector<std::vector<Type>> result(height, std::vector<Type>(width));

			data.resize(height);
			for (auto &d : data)
				d.resize(width);

			ivec2 pos;
			for (const auto &line : lines)
			{
				for (const auto &c : line)
				{
					data[pos.y()][pos.x()] = c;
					pos[0]++;
				}
				pos[1]++;
				pos[0] = 0;
			}
			recalc_size();
		}

		// read from file
		void read(std::string_view filename)
		{
			auto lines = read_lines(filename);
			from_lines(lines);
			recalc_size();
		}

		// column
		VecType column(i64 x) const
		{
			VecType ret;

			for (i64 y = 0; y < height; ++y)
				ret.emplace_back(at(x, y));

			return ret;
		}

		// column_as_string
		std::string column_as_string(i64 x) const
		{
			std::string ret;
			auto        r = column(x);
			ret.reserve(r.size());

			for (const char &i : r)
				ret += i;
			return ret;
		}

		// row
		VecType row(i64 y) const
		{
			VecType ret;

			for (i64 x = 0; x < width; ++x)
				ret.emplace_back(at(x, y));

			return ret;
		}

		// row_as_string
		std::string row_as_string(i64 y) const
		{
			std::string ret;
			auto        r = row(y);
			ret.reserve(r.size());

			for (const char &i : r)
				ret += i;
			return ret;
		}

		// columns
		std::vector<VecType> columns() const
		{
			std::vector<VecType> ret;

			for (i64 x = 0; x < width; ++x)
				ret.push_back(column(x));

			return ret;
		}

		// rows
		std::vector<VecType> rows() const
		{
			std::vector<VecType> ret;

			for (i64 y = 0; y < width; ++y)
				ret.push_back(row(y));

			return ret;
		}

		// transpose
		//
		// 123    147
		// 456 => 258
		// 789    369
		void transpose() noexcept
		{
			std::vector<std::vector<char>> result(width, std::vector<char>(height));

			for (i64 y = 0; y < height; ++y)
				for (i64 x = 0; x < width; ++x)
					result[x][y] = data[y][x];

			data = result;

			dbgln("Warning: visited map reset on transpose");
			recalc_size();
		}

		// rotate cw 90
		void rotate_cw_90() noexcept
		{
			transpose();
			reverse_rows();
		}

		// rotate ccw 90
		void rotate_ccw_90() noexcept
		{
			transpose();
			reverse_columns();
		}

		void rotate_180() noexcept { reverse_rows_and_columns(); }

		// reverse
		void reverse_columns() noexcept { std::ranges::reverse(data); }

		void reverse_rows() noexcept
		{
			for (auto &row : data)
				std::ranges::reverse(row);
		}

		void reverse_rows_and_columns() noexcept
		{
			reverse_columns();
			reverse_rows();
		}

		bool valid(i64 x, i64 y) const noexcept { return (x >= 0 && x < width) && (y >= 0 && y < height); }

		bool valid(ivec2 pos) const noexcept { return valid(pos[0], pos[1]); }

		// set
		void set(i64 x, i64 y, Type value) noexcept
		{
			if (valid(x, y))
				set_unsafe(x, y, value);
			else
				dbgln("grid2d: trying to set out-of-bounds: {}", ivec2(x, y));
		}

		void set(ivec2 pos, Type value) noexcept { set(pos[0], pos[1], value); }

		// set_unsafe
		void set_unsafe(const ivec2 pos, Type value) noexcept { set_unsafe(pos[0], pos[1], value); }

		void set_unsafe(i64 x, i64 y, Type value) noexcept { data[y][x] = value; }

		// fill
		void fill(Type value = '.')
		{
			for (i64 y = 0; y < height; ++y)
				for (i64 x = 0; x < width; ++x)
					set_unsafe(x, y, value);
		}

		// flood fill
		void floodfill(ivec2 pos, Type filler) { floodfill(pos, at(pos), filler); }

		void floodfill(ivec2 pos, Type target, Type filler) { floodfill(pos[0], pos[1], target, filler); }

		void floodfill(i64 x, i64 y, Type target, Type filler)
		{
			std::unordered_set<ivec2> seen;
			std::deque<ivec2>         to_visit;
			to_visit.push_back({x, y});

			while (!to_visit.empty())
			{
				auto pos = to_visit.front();
				to_visit.pop_front();

				if (!valid(pos))
					continue;
				if (seen.contains(pos))
					continue;
				seen.insert(pos);

				if (at_unsafe(pos) != target)
					continue;

				set_unsafe(pos, filler);

				to_visit.push_back({pos + right});
				to_visit.push_back({pos + left});
				to_visit.push_back({pos + up});
				to_visit.push_back({pos + down});
			}
		}

		// at_unsafe
		Type at_unsafe(i64 x, i64 y) const noexcept { return data[y][x]; }

		Type &at_unsafe(i64 x, i64 y) noexcept { return data[y][x]; }

		Type at_unsafe(const ivec2 pos) const noexcept { return data[pos[1]][pos[0]]; }

		Type &at_unsafe(const ivec2 pos) noexcept { return data[pos[1]][pos[0]]; }

		// at
		Type at(i64 x, i64 y) const noexcept
		{
			if (valid(x, y))
				return at_unsafe(x, y);

			dbgln("grid2d: indexing out of bounds: {}", ivec2(x, y));
			static Type ret = '\0';
			return ret;
		}

		Type &at(i64 x, i64 y) noexcept
		{
			if (valid(x, y))
				return at_unsafe(x, y);

			dbgln("grid2d: indexing out of bounds: {}", ivec2(x, y));
			static Type ret = '\0';
			return ret;
		}

		Type &at(ivec2 pos) noexcept { return at(pos[0], pos[1]); }

		Type at(ivec2 pos) const noexcept { return at(pos[0], pos[1]); }

		// operator() / at
		char operator()(i64 x, i64 y) const noexcept { return at(x, y); }

		char &operator()(i64 x, i64 y) noexcept { return at(x, y); }

		char operator()(const ivec2 pos) const noexcept { return at(pos[0], pos[1]); }

		char &operator()(const ivec2 pos) noexcept { return at(pos[0], pos[1]); }

		// move
		void move(ivec2 pos, ivec2 newpos)
		{
			if (valid(pos) && valid(newpos))
				std::swap(at_unsafe(pos), at_unsafe(newpos));
			else
				dbgln("grid2d::move({},{}) - both coords need to be valid", pos, newpos);
		}

		void print() const noexcept
		{
			dbgln();
			for (i64 y = 0; y < height; ++y)
			{
				for (i64 x = 0; x < width; ++x)
				{
					dbg("{}", at(x, y));
				}
				dbgln();
			}
			dbgln();
		}

		void swap(grid2d &other) noexcept
		{
			using std::swap;
			swap(width, other.width);
			swap(height, other.height);
			swap(data, other.data);
		}

		grid2d &operator=(grid2d lhs) noexcept
		{
			swap(lhs);
			return *this;
		}

		bool operator==(const grid2d &lhs) const noexcept
		{
			//
			return width == lhs.width && height == lhs.height && data == lhs.data;
		}

		// hash
		operator hash_type() const noexcept { return hash(); }

		// hash
		hash_type hash(size_t seed = 0) const noexcept
		{
			hash_combine(seed, width, height);

			for (i64 y = 0; y < height; ++y)
				for (i64 x = 0; x < width; ++x)
					hash_combine(seed, data[y][x]);
			return seed;
		}

		// recalc
		void recalc_size() noexcept
		{
			width  = data[0].size();
			height = data.size();

			visited_map.resize(width * height);
		}

		// reset
		void reset()
		{
			width  = 0;
			height = 0;
			data.clear();
			visited_map.clear();
		}

		// count
		i64 count(std::string_view input) const noexcept
		{
			i64 count = 0;
			for (i64 y = 0; y < height; ++y)
				for (i64 x = 0; x < width; ++x)
					count += input.contains(at(x, y)) ? 1 : 0;
			return count;
		}

		std::vector<std::vector<Type>> data;
		i64                            width{0};
		i64                            height{0};

		// visited
		std::vector<u8> visited_map;

		void visit(const ivec2 pos, u8 value = 1) { visit(pos[0], pos[1], value); }

		void visit(i64 x, i64 y, u8 value = 1)
		{
			if (valid(x, y))
				visited_map[*index2D(x, y, width, height)] |= value;
		}

		u8 visited(const ivec2 pos) const { return visited(pos[0], pos[1]); }

		u8 visited(i64 x, i64 y) const
		{
			if (valid(x, y))
				return visited_map[*index2D(x, y, width, height)];
			else
			{
				dbgln("grid2d::visited({},{}) invalid position", x, y);
				return '\0';
			}
		}

		void clear_visited() noexcept { std::ranges::fill(visited_map, static_cast<u8>(0)); }
	};

} // export

// STD specials
export namespace std

{

	template<>
	struct hash<grid2d>
	{
		grid2d::hash_type operator()(const grid2d &grid) const { return grid.hash(); }
	};

} // namespace std
