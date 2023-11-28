export module aoc.sprite;

import std;
import aoc.debug;
import aoc.readfile;
import aoc.vec;

export class sprite final
{
public:
	using Type = char;

	sprite() = default;

	sprite(int w, int h)
	{
		width  = w;
		height = h;
		m_data.resize(width * height);
	}

	sprite(std::string_view filename) { read(filename); }

	void read(std::string_view filename)
	{
		auto lines = read_lines(filename);
		width      = lines[0].size();
		height     = lines.size();
		m_data.clear();
		m_data.resize(width * height);
		ivec2 pos;
		for (const auto &row : lines)
		{
			pos[0] = 0;
			for (const auto &c : row)
			{
				set(pos, c);
				pos[0]++;
			}
			pos[1]++;
		}
	}

	void flip_horizontal()
	{
		//
		for (auto i = 0; i < height; ++i)
		{
			for (auto j = 0; j < width / 2; ++j)
			{
				std::swap((*this)(j, i), (*this)(width - 1 - j, i));
			}
		}
	}

	void flip_vertical()
	{
		std::vector<Type> result(m_data.size());

		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				result[i * width + j] = m_data[(height - i - 1) * width + j];
			}
		}

		m_data = result;
	}

	void transpose()
	{
		std::vector<Type> result(m_data.size());

		for (auto i = 0; i < height; ++i)
		{
			for (auto j = 0; j < width; ++j)
			{
				result[j * height + i] = m_data[i * width + j];
			}
		}
		m_data = result;
		std::swap(width, height);
	}

	void rotate_cw()
	{
		std::vector<Type> result(m_data.size());

		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				result[j * height + (height - i - 1)] = m_data[i * width + j];
			}
		}

		m_data = result;
		std::swap(width, height);
	}

	void rotate_ccw()
	{
		std::vector<Type> result(m_data.size());

		for (size_t i = 0; i < height; ++i)
		{
			for (size_t j = 0; j < width; ++j)
			{
				result[(width - j - 1) * height + i] = m_data[i * width + j];
			}
		}

		m_data = result;
		std::swap(width, height);
	}

	size_t index(ivec2 pos) const { return pos.y() * width + pos.x(); }

	Type &operator()(i64 x, i64 y)
	{
		const ivec2 pos(x, y);
		if (is_valid(pos))
			return m_data[index(pos)];

		dbgln("indexing invalid position {}", pos);

		static char placeholder = '\0';
		return placeholder;
	}

	Type &operator()(ivec2 pos) { return (*this)(pos.x(), pos.y()); }

	const Type &operator()(i64 x, i64 y) const
	{
		ivec2 pos(x, y);
		if (is_valid(pos))
			return m_data[index(pos)];

		dbgln("indexing invalid position {}", pos);
		static const char placeholder = '\0';
		return placeholder;
	}

	const Type &operator()(ivec2 pos) const { return (*this)(pos.x(), pos.y()); }

	void set(ivec2 pos, Type value)
	{
		if (is_valid(pos))
			m_data[index(pos)] = value;
	}

	void add(ivec2 pos, Type value) { m_data[index(pos)] += value; }

	void fill(Type value)
	{
		for (size_t y = 0; y < height; ++y)
		{
			for (size_t x = 0; x < width; ++x)
			{
				set(ivec2(x, y), value);
			}
		}
	}

	bool is_valid(ivec2 pos) const { return pos >= ivec2(0, 0) && pos <= ivec2(width, height); }

	void print() const
	{
		dbgln("sprite: bounds {}", ivec2(width, height));
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				dbg("{}", m_data[index(ivec2(j, i))]);
			}
			dbg("\n");
		}
		dbgln();
	}

private:
	size_t width{0};
	size_t height{0};

	std::vector<Type> m_data;
};
