module;
#include "glm/glm.hpp"
#include "standard.h"

export module math;
import types;
import standard;


export
{

	template<typename T>
	struct vec2_helper
	{
		vec2_helper() = default;

		vec2_helper(T one)
			: x(one)
			, y(one)
		{
		}

		vec2_helper(T one, T two)
			: x(one)
			, y(two)
		{
		}

		T x{};
		T y{};

		constexpr vec2_helper abs() const noexcept { return vec2_helper{std::abs(x), std::abs(y)}; }

		vec2_helper &operator-() const
		{
			x = -x;
			y = -y;
			return *this;
		}

		constexpr vec2_helper operator*(T other) noexcept
		{
			x *= other;
			y *= other;
			return *this;
		}

		constexpr vec2_helper &operator*=(const vec2_helper &other) noexcept
		{
			x *= other.x;
			y *= other.y;
			return *this;
		}

		constexpr vec2_helper &operator+=(const vec2_helper &other) noexcept
		{
			x += other.x;
			y += other.y;
			return *this;
		}

		constexpr vec2_helper &operator-=(const vec2_helper &other) noexcept
		{
			x -= other.x;
			y -= other.y;
			return *this;
		}

		constexpr T max() const noexcept { return std::max(x, y); }

		vec2_helper operator+(const vec2_helper &b) const { return vec2_helper{x + b.x, y + b.y}; }

		vec2_helper operator-(const vec2_helper &b) const { return vec2_helper{x - b.x, y - b.y}; }

		vec2_helper operator*(const vec2_helper &b) const { return vec2_helper{x * b.x, y * b.y}; }

		vec2_helper operator*(const T scalar) const { return vec2_helper{scalar * x, scalar * y}; }

		bool empty() const { return (x == 0 && y == 0); };

		auto operator<=>(const vec2_helper &v) const
		{
			if (x != v.x)
				return x <=> v.x;
			if (y != v.y)
				return y <=> v.y;
			return std::strong_ordering::equal;
		}

		bool operator==(const vec2_helper &v) const { return x == v.x && y == v.y; }
	};

	using ivec2 = vec2_helper<i64>;
	using uvec2 = vec2_helper<u64>;

	STD_HASH(ivec2, value.x, value.y)

	const ivec2 IVEC2_MAX(MAX_I64, MAX_I64);
	const ivec2 IVEC2_MIN(MIN_I64, MIN_I64);
	//
	// Math
	ivec2 abs(const ivec2 &) noexcept;

	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/

	struct line
	{
		line(ivec2 a, ivec2 b)
			: p1(a)
			, p2(b)
		{
		}

		ivec2 p1;
		ivec2 p2;
	};

	std::optional<ivec2> intersect(const ivec2 &a, const ivec2 &b, const ivec2 &c, const ivec2 &d) noexcept;
	std::optional<ivec2> intersect(const line &a, const line &b) noexcept;
	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/


	bool randbool();


	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/

	template<typename T = i64>
	T manhattan_distance(T a, T b) noexcept
	{
		return as<T>(std::abs(a) + std::abs(b));
	}

	template<typename T = i64>
	T manhattan_distance(ivec2 a, ivec2 b = {0, 0}) noexcept
	{
		return manhattan_distance<T>(a.x - b.x, a.y - b.y);
	}

	i64 mod(i64 x, i64 N) noexcept;
	i64 modinv(i64 a, i64 b) noexcept;

	template<typename T>
	inline T modpow(T base, T exp, T modulus)
	{
		base %= modulus;
		T result = 1;
		while (exp)
		{
			if (exp & 1)
				result = (result * base) % modulus;
			base = (base * base) % modulus;
			exp >>= 1;
		}
		return result;
	}

	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/

	bool between(i64, i64, i64) noexcept;

	template<class A, class... Args>
	inline constexpr A vlcm(A a, A b, Args... args)
	{
		return std::lcm(std::lcm(a, b), args...);
	}

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

	// vmin
	template<typename T>
	const T &vmin(const T &a)
	{
		return a;
	}
	template<typename T, typename... Args>
	const T &vmin(const T &a, const T &b, const Args &...args)
	{
		if constexpr (sizeof...(args) == 0)
			return std::min(a, b);
		else
			return std::min(std::min(a, b), args...);
	}

	template<class A, class... Args>
	inline constexpr A vmodulus(A a, A b, Args... args)
	{
		return std::modulus(std::modulus(a, b), args...);
	}

	template<typename T>
	inline constexpr T lcm_compute(const T a, const T b) noexcept
	{
		return abs(a * (b / gcd(a, b)));
	}

	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/

	template<typename T>
	struct vec3_helper
	{
		T x{};
		T y{};
		T z{};

		T offset(vec3_helper b) const { return std::abs(b.x - x) + std::abs(b.y - y) + std::abs(b.z - z); }

		i64 offset_hash(const vec3_helper &b)
		{
			i64 seed{0};
			hash_combine(seed, b.x - x, b.y - y, b.z - z);
			return seed;
		}

		constexpr void rotate(int xyz)
		{
			if (xyz == 2) // Z
			{
				T temp = x;
				x      = -y;
				y      = temp;
			}
			else if (xyz == 1) // Y
			{
				T temp = x;
				x      = -z;
				z      = temp;
			}
			else // X
			{
				T temp = y;
				y      = -z;
				z      = temp;
			}
		}

		constexpr void negate(int xyz)
		{
			if (xyz == 2)
				z = -z;
			else if (xyz == 1)
				y = -y;
			else
				x = -x;
		}

		constexpr vec3_helper &operator+=(const vec3_helper &other) noexcept
		{
			x += other.x;
			y += other.y;
			z += other.z;
			return *this;
		}

		constexpr vec3_helper &operator-=(const vec3_helper &other) noexcept
		{
			x -= other.x;
			y -= other.y;
			z -= other.z;
			return *this;
		}

		vec3_helper operator+(const vec3_helper &b) const { return vec3_helper{x + b.x, y + b.y, z + b.z}; }

		vec3_helper operator-(const vec3_helper &b) const { return vec3_helper{x - b.x, y - b.y, z - b.z}; }

		auto operator<=>(const vec3_helper &v) const
		{
			if (x != v.x)
				return x <=> v.x;
			if (y != v.y)
				return y <=> v.y;
			return z <=> v.z;
		}

		i64 operator[](int index) const
		{
			if (index == 0)
				return x;
			if (index == 1)
				return y;
			if (index == 2)
				return z;
			if (index > 2)
				std::terminate();
		}

		bool operator==(const vec3_helper &other) const { return x == other.x && y == other.y && z == other.z; }
	};

	using ivec3   = vec3_helper<i64>;
	using i32vec3 = vec3_helper<int>;

	using uvec3 = vec3_helper<u64>;

	inline i64 dist(const ivec3 a, const ivec3 &b = {}) noexcept;
	i64        manhattan_distance(ivec3 p1, ivec3 p2) noexcept;

	STD_HASH(ivec3, value.x, value.y, value.z)

	ivec3 max(const ivec3 &a, const ivec3 &b) noexcept;
	ivec3 min(const ivec3 &a, const ivec3 &b) noexcept;

	template<typename T>
	using ivec2map = std::unordered_map<ivec2, T>;
	template<typename T>
	using ivec3map = std::unordered_map<ivec3, T>;


	using ivec4 = glm::vec<4, i64, glm::defaultp>;
	/*
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	###############################################################################
	*/


	const ivec2 north{0, -1};
	const ivec2 east{1, 0};
	const ivec2 south{0, 1};
	const ivec2 west{-1, 0};
	const ivec2 north_east{north + east};
	const ivec2 north_west{north + west};
	const ivec2 south_east{south + east};
	const ivec2 south_west{south + west};

	const std::vector<ivec2> directions_4_way{
		north,
		east,
		south,
		west,
	};

	const std::vector<ivec2> directions_4_diag{
		south_west,
		south_east,
		north_west,
		north_east,
	};

	const std::vector<ivec2> directions_8_way{
		north,
		east,
		south,
		west,

		north_east,
		north_west,
		south_east,
		south_west,
	};

	const std::unordered_map<i64, glm::ivec2> directions_4_way_umap = {
		{0, glm::ivec2(0, 1)},    // North
		{270, glm::ivec2(1, 0)},  // East
		{180, glm::ivec2(0, -1)}, // South
		{90, glm::ivec2(-1, 0)},  // West
	};

	const std::array<glm::ivec2, 4> directions_4 = {
		glm::ivec2(0, 1),
		glm::ivec2(1, 0),
		glm::ivec2(0, -1),
		glm::ivec2(-1, 0),
	};
}
