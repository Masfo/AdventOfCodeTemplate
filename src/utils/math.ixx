
export module aoc.math;
import std;
import aoc.types;

export
{

	// vmax
	template<typename T>
	const T vmax(const T &a)
	{
		return a;
	}

	template<typename T, typename... Args>
	const T &vmax(const T &a, const T &b, const Args &...args)
	{
		if constexpr (sizeof...(args) == 0)
			return std::max(a, b);
		else
			return std::max(std::min(a, b), args...);
	}

	struct ivec2
	{
		i64 x;
		i64 y;
	};

	struct ivec3
	{
		i64 x;
		i64 y;
		i64 z;
	};

	struct ivec4
	{
		i64 x;
		i64 y;
		i64 z;
		i64 w;
	};
}
