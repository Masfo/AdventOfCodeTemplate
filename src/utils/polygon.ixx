export module aoc.polygon;
import std;
import aoc.vec;
import aoc.types;
import aoc.math;
export
{

	class polygon2d final
	{
	public:
		using Type = i64;

		void reset()
		{
			vertices.clear();
			poly_area = poly_perimeter = 0;
		}

		void insert(Type x, Type y) { insert(ivec2(x, y)); }

		void insert(ivec2 p) { vertices.push_back(p); }

		Type area() noexcept
		{
			calc();
			return poly_area;
		}

		Type perimeter() noexcept
		{
			calc();

			return poly_perimeter;
		}

		Type total_area() noexcept
		{
			calc();

			return poly_area + poly_perimeter;
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

		void calc() noexcept
		{
			// if(vertices.size())
			//  Shoelace formula
			poly_area      = 0;
			poly_perimeter = 0;
			for (size_t i = 0; i < vertices.size(); ++i)
			{
				size_t j = (i + 1) % vertices.size();

				poly_area += vertices[i][0] * vertices[j][1];
				poly_area -= vertices[j][0] * vertices[i][1];

				poly_perimeter += distance(vertices[i], vertices[j]);
			}

			poly_area = std::abs(poly_area) / 2;
			poly_area = (poly_area - (poly_perimeter / 2) + 1);
		}

		Type poly_perimeter = 0;
		Type poly_area      = 0;

		std::vector<ivec2> vertices;
		//
	};

} // export
