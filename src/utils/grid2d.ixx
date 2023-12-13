export module aoc.grid2d;

import std;
import aoc.types;
import aoc.vec;
import aoc.debug;
import aoc.readfile;
import aoc.stringsplit;

// grid2d
export
{

	struct grid2d final
	{
		using Type    = char;
		using VecType = std::vector<char>;

		grid2d() = default;

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
		}

		// read from file
		void read(std::string_view filename)
		{
			auto lines = read_lines(filename);
			from_lines(lines);
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

		// at
		char at(i64 x, i64 y) const noexcept
		{
			if (valid(x, y))
			{
				return data[y][x];
			}
			dbgln("grid2d: indexing out of bounds: {}", ivec2(x, y));
			static char ret = '\0';
			return ret;
		}

		// at
		char &at(i64 x, i64 y) noexcept
		{
			if (valid(x, y))
			{
				return data[y][x];
			}
			dbgln("grid2d: indexing out of bounds: {}", ivec2(x, y));
			static char ret = '\0';
			return ret;
		}

		void print() const noexcept
		{
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

		char operator()(i64 x, i64 y) const noexcept { return at(x, y); }

		char &operator()(i64 x, i64 y) noexcept { return at(x, y); }

		void recalc_size() noexcept
		{
			width  = data[0].size();
			height = data.size();
		}

		void reset()
		{
			width  = 0;
			height = 0;
			data.clear();
		}

		std::vector<std::vector<Type>> data;
		i64                            width{0};
		i64                            height{0};
	};

} // export
