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

export class ppm
{
public:
	ppm(u16 w, u16 h)
		: width(w)
		, height(h)
	{
		image.resize(width * height);
		fill({0, 0, 0});
	}

	void fill(rgb color) { std::ranges::fill(image, color); }

	void put(ivec2 coord, rgb color) { put(coord[0], coord[1], color); }

	void put(i64 x, i64 y, rgb color)
	{
		//
		if (x <= width && y <= height)
			image[y * width + x] = color;
		else
			dbgln("trying to index outside image {}x{} != {}x{}", x, y, width, height);
	}

	void line(ivec2 v1, ivec2 v2, rgb color)
	{
		ivec2 delta;
		if (v2[0] - v1[0] != 0)
			delta[0] = v2[0] - v1[0] > 0 ? 1 : -1;
		if (v2[1] - v1[1] != 0)
			delta[1] = v2[1] - v1[1] > 0 ? 1 : -1;

		put(v1, color);

		while (v1.x() != v2.x() || v1.y() != v2.y())
		{
			v1 += delta;
			put(v1, color);
		}
	}

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
	u16              width{0};
	u16              height{0};
	std::vector<rgb> image;
};
