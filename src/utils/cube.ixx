export module aoc.cube;
import std;
import aoc.math;
import aoc.vec;

export
{

	struct cube final
	{
		cube() = default;

		cube(ivec3 f, ivec3 l, i64 o = -1)
			: first(f)
			, last(l)
			, on(o)
		{
		}

		i64 length(int index) { return last[index] - first[index]; }

		i64 high(int index) { return std::max(first[index], last[index]); }

		i64 low(int index) { return std::min(first[index], last[index]); }

		u64 volume() const { return (1ull + last[0] - first[0]) * (1ull + last[1] - first[1]) * (1ull + last[2] - first[2]); }

		bool intersects(const cube& b) const
		{
			if (first[0] > b.last[0] || last[0] < b.first[0] || first[1] > b.last[1] || last[1] < b.first[1] || first[2] > b.last[2] ||
				last[2] < b.first[2])
				return false;
			return true;
		}

		std::optional<cube> intersection(const cube& b) const
		{
			if (!intersects(b))
				return {};

			return cube{{std::max(first[0], b.first[0]), std::max(first[1], b.first[1]), std::max(first[2], b.first[2])},
						{std::min(last[0], b.last[0]), std::min(last[1], b.last[1]), std::min(last[2], b.last[2])},
						-b.on};
		}

		void move(ivec3 offset)
		{
			first += offset;
			last += offset;
		}

		constexpr auto operator<=>(const cube& other) const noexcept = default;

		ivec3 first, last;
		i64   on{-1};

		// sorts:  std::vector<cube> cubes;
		//         std::ranges::sort(cubes, cube::x);
		static bool x(const cube& c1, const cube& c2) { return c1.first[0] < c2.first[0]; }

		static bool y(const cube& c1, const cube& c2) { return c1.first[1] < c2.first[1]; }

		static bool z(const cube& c1, const cube& c2) { return c1.first[2] < c2.first[2]; }
	};

	//
	// Cuboid
	// 	struct cuboid
	// 	{
	// 		cuboid() = default;
	//
	// 		cuboid(const ivec3& min, const ivec3& max, i64 on = 1)
	// 			: min(min)
	// 			, max(max)
	// 			, on(on)
	// 		{
	// 		}
	//
	// 		ivec3 min, max;
	// 		i64   on{-1};
	//
	// 		u64 volume() const { return (1ull + max[0] - min[0]) * (1ull + max[1] - min[1]) * (1ull + max[2] - min[2]); }
	//
	// 		std::optional<cuboid> intersects(const cuboid& b) const
	// 		{
	// 			if (!collides(b))
	// 				return {};
	//
	// 			return cuboid{{std::max(min[0], b.min[0]), std::max(min[1], b.min[1]), std::max(min[2], b.min[2])},
	// 						  {std::min(max[0], b.max[0]), std::min(max[1], b.max[1]), std::min(max[2], b.max[2])},
	// 						  -b.on};
	// 		}
	//
	// 		bool collides(const cuboid& b) const
	// 		{
	// 			if (min[0] > b.max[0] ||
	//              max[0] < b.min[0] ||
	//              min[1] > b.max[1] ||
	//              max[1] < b.min[1] ||
	//              min[2] > b.max[2] ||
	//             max[2] < b.min[2])
	//  				return false;
	//           return true;
	// 		}
	//
	// 		void move(ivec3 pos)
	// 		{
	// 			min += pos;
	// 			max += pos;
	// 		}
	//
	// 		constexpr auto operator<=>(const cuboid& other) const noexcept = default;
	// 	};

} // export

export namespace std

{

	template<>
	struct hash<cube>
	{
		size_t operator()(const cube& c) const { return hash_values(c.first, c.last, c.on); }
	};

} // namespace std
