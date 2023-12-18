export module aoc.ppm;
import std;
import aoc.debug;
import aoc.types;
import aoc.vec;

/*
	u16 width  = 256;
	u16 height = 256;

	ppm p(width, height);

	for (int y = 0; y < height; ++y)
		for (int x = 0; x < width; ++x)
		{
			u8 c = x ^ y;
			p.put(x, y, rgb(c, c, c));
		}

	p.line({0, 0}, {128, 128}, rgb(255, 255, 255));
	p.write("spec.ppm");

*/

export class static_ppm
{
public:
	static_ppm(i64 w, i64 h)
		: width(w)
		, height(h)
	{
		image.resize(width * height);
		fill({255, 255, 255});
	}

	void fill(rgb color) { std::ranges::fill(image, color); }

	void put(ivec2 coord, rgb color) { put(coord[0], coord[1], color); }

	void put(i64 x, i64 y, rgb color)
	{
		//
		if (auto index = index2D(x, y, width, height); index)
			image[*index] = color;
		else
			dbgln("trying to index outside image {}x{} != {}x{}", x, y, width, height);
	}

	void line(i64 x1, i64 y1, i64 x2, i64 y2, rgb color)
	{
		i64 dx = std::abs(x2 - x1);
		i64 dy = std::abs(y2 - y1);
		i64 sx = (x1 < x2) ? 1 : -1;
		i64 sy = (y1 < y2) ? 1 : -1;

		i64 err = dx - dy;

		while (true)
		{
			put(x1, y1, color);

			if (x1 == x2 && y1 == y2)
				break;

			i64 e2 = 2 * err;

			if (e2 > -dy)
			{
				err -= dy;
				x1 += sx;
			}

			if (e2 < dx)
			{
				err += dx;
				y1 += sy;
			}
		}
	}

	void line(ivec2 v1, ivec2 v2, rgb color) { line(v1[0], v1[1], v2[0], v2[1], color); }

	bool write(const std::string &filename)
	{
		std::ofstream file(filename, std::ios::out | std::ios::binary);
		if (!file)
		{
			dbgln("ppm: file not opened '{}'", filename);
			return false;
		}

		file << "P6\n" << width << " " << height << "\n255\n";

		file.write(reinterpret_cast<const char *>(image.data()), width * height * 3);

		dbgln("ppm: wrote '{}' ({}x{})", filename, width, height);
		file.close();

		return true;
	}

private:
	i64              width{0};
	i64              height{0};
	std::vector<rgb> image;
};

export class ppm
{
public:
	ppm() = default;

	ppm(rgb fc)
		: fill_color(fc)
	{
	}

	void put(ivec2 coord, rgb color) { put(coord[0], coord[1], color); }

	void put(i64 x, i64 y, rgb color) { image[ivec2{x, y}] = color; }

	void line(i64 x1, i64 y1, i64 x2, i64 y2, rgb color)
	{
		i64 dx = std::abs(x2 - x1);
		i64 dy = std::abs(y2 - y1);
		i64 sx = (x1 < x2) ? 1 : -1;
		i64 sy = (y1 < y2) ? 1 : -1;

		i64 err = dx - dy;

		while (true)
		{
			put(x1, y1, color);

			if (x1 == x2 && y1 == y2)
				break;

			i64 e2 = 2 * err;

			if (e2 > -dy)
			{
				err -= dy;
				x1 += sx;
			}

			if (e2 < dx)
			{
				err += dx;
				y1 += sy;
			}
		}
	}

	void line(ivec2 v1, ivec2 v2, rgb color) { line(v1[0], v1[1], v2[0], v2[1], color); }

	bool write(const std::string &filename)
	{
		ivec2 mmin = MAX_IVEC2, mmax = MIN_IVEC2;
		for (const auto &[pos, _] : image)
		{
			mmin = min(mmin, pos);
			mmax = max(mmax, pos);
		}
		ivec2      res    = mmax - mmin;
		ivec2      offset = mmin.abs();
		ivec2      border(10, 10);
		ivec2      half{border / 2};
		static_ppm img(border[0] + res[0], border[1] + res[1]);
		img.fill(fill_color);

		for (const auto &[pos, color] : image)
			img.put(half + pos + offset, color);

		return img.write(filename);
	}

private:
	rgb                            fill_color{255, 255, 255};
	std::unordered_map<ivec2, rgb> image;
};
