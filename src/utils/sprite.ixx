export module aoc.sprite;

import std;
import aoc.debug;
import aoc.readfile;
import aoc.vec;

export class sprite
{
public:
	using Type = char;

	sprite() = default;

	sprite(std::string_view filename) { read(filename); }

	void read(std::string_view filename)
	{
		auto lines = read_lines(filename);
		width      = lines[0].size();
		height     = lines.size();
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
	}

	void flip_vertical()
	{
		//
	}

	void transpose()
	{
		//
	}

	size_t index(ivec2 pos) const { return pos.y() * width + pos.x(); }

	Type &operator()(ivec2 pos)
	{
		if (is_valid(pos))
			return m_data[index(pos)];

		dbgln("indexing invalid position {}", pos);

		static char placeholder = '\0';
		return placeholder;
	}

	const Type &operator()(ivec2 pos) const
	{
		if (is_valid(pos))
			return m_data[index(pos)];

		dbgln("indexing invalid position {}", pos);
		static const char placeholder = '\0';
		return placeholder;
	}

	void set(ivec2 pos, Type value)
	{
		if (is_valid(pos))
			m_data[index(pos)] = value;
	}

	bool is_valid(ivec2 pos) const { return pos >= ivec2(0, 0) && pos <= ivec2(width, height); }

	void print() const
	{
		for (int i = 0; i < height; ++i)
		{
			for (int j = 0; j < width; ++j)
			{
				dbg("{}", m_data[index(ivec2(j, i))]);
			}
			dbg("\n");
		}
	}

private:
	size_t width{0};
	size_t height{0};

	std::vector<Type> m_data;
};
