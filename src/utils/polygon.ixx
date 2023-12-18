export module aoc.polygon;
import std;
import aoc.vec;
import aoc.types;
import aoc.math;
import aoc.debug;

// 3 + 13/2-1
export
{

	class polygon2d final
	{
	public:
		using Type = i64;

		void reset()
		{
			vertices.clear();
			interior_count = boundary_count = 0;
		}

		void insert(Type x, Type y) { insert(ivec2(x, y)); }

		void insert(ivec2 p) { vertices.push_back(p); }

		Type interior() noexcept
		{
			calc();
			return interior_count;
		}

		Type boundary() noexcept
		{
			calc();

			return boundary_count;
		}

		Type total_area() noexcept
		{
			calc();

			return interior_count + boundary_count;
		}

	private:
		/*
		 * Area(.):      24
		 * Perimeter(#): 38
		 * Total:        62

		   #######
		   #.....#
		   ###...#
			#...#
			#...#
		   ###.###
		   #...#
		   ##..###
			#....#
			######
		 */

		Type shoelace_theorem() noexcept
		{
			// https://artofproblemsolving.com/wiki/index.php/Shoelace_Theorem

			if (vertices.size() < 3)
			{
				dbgln("polygon2d: need at least 3 vertices");
				return -1;
			}

			i64 area       = 0;
			boundary_count = 0;
			for (size_t i = 0; i < vertices.size(); ++i)
			{
				size_t j = (i + 1) % vertices.size();

				area += vertices[i][0] * vertices[j][1];
				area -= vertices[j][0] * vertices[i][1];

				boundary_count += distance(vertices[i], vertices[j]);
			}
			return std::abs(area) / 2;
		}

		void calc() noexcept
		{
			// Pick's Theorem: https://artofproblemsolving.com/wiki/index.php/Pick%27s_Theorem
			interior_count = (shoelace_theorem() - (boundary_count / 2) + 1);
		}

		Type boundary_count = 0;
		Type interior_count = 0;

		std::vector<ivec2> vertices;
		//
	};

} // export
