module;
#pragma once

// #include "glm.hpp"


export module aoc.math;
import aoc.vec;
import std;
import aoc.types;


#define STD_HASH(T, ...)                                                                                                                   \
	namespace std                                                                                                                          \
	{                                                                                                                                      \
		template<>                                                                                                                         \
		struct hash<T>                                                                                                                     \
		{                                                                                                                                  \
			size_t operator()(const T &value) const {return hash_val(__VA_ARGS__)); }                                                      \
		};                                                                                                                                 \
	}


export
{

	// common
	i64 mod(i64 x, i64 N) noexcept
	{
		if (N == 0)
			return 0;
		return (x % N + N) % N;
	}
	i64 modinv(i64 a, i64 b) noexcept
	{
		// Extended Euclidean Algorithm and Modular Inverse, from
		// <https://github.com/PetarV-/Algorithms/blob/master/

		// The MIT License (MIT)

		// Copyright (c) 2015 Petar Velickovic

		// Permission is hereby granted, free of charge, to any person obtaining a
		// copy of this software and associated documentation files (the "Software"),
		// to deal in the Software without restriction, including without limitation
		// the rights to use, copy, modify, merge, publish, distribute, sublicense,
		// and/or sell copies of the Software, and to permit persons to whom the
		// Software is furnished to do so, subject to the following conditions:

		// The above copyright notice and this permission notice shall be included in
		// all copies or substantial portions of the Software.

		// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
		// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
		// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
		// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
		// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
		// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
		// DEALINGS IN THE SOFTWARE.
		i64 b0 = b;
		i64 aa = 1, ba = 0;
		while (true)
		{
			i64 q = a / b;
			if (a == b * q)
			{
				if (b != 1)
				{
					// Modular inverse does not exist!
					return -1;
				}
				while (ba < 0)
					ba += b0;
				return ba;
			}
			i64 tmp_a  = a;
			i64 tmp_aa = aa;
			a          = b;
			b          = tmp_a - b * q;
			aa         = ba;
			ba         = tmp_aa - ba * q;
		}
	}


	bool between(i64 value, i64 a, i64 b) noexcept { return value >= a && value <= b; }


	template<typename T = i64>
	T manhattan_distance(T a, T b) noexcept
	{
		return as<T>(std::abs(a) + std::abs(b));
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

	// vmod
	template<class A, class... Args>
	inline constexpr A vmodulus(A a, A b, Args... args)
	{
		return std::modulus(std::modulus(a, b), args...);
	}

	// lcm
	template<typename T>
	inline constexpr T lcm_compute(const T a, const T b) noexcept
	{
		return abs(a * (b / gcd(a, b)));
	}
#if 0
	// ########################################################
	// VEC2
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

	STD_HASH(ivec2, value.x, value.y);

	ivec2 abs(const ivec2 &v) noexcept { return {std::abs(v.x), std::abs(v.y)}; }


	// vec3
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

	i64 dist(const ivec3 a, const ivec3 &b) noexcept
	{
		i64 dx = std::abs(b.x - a.x);
		i64 dy = std::abs(b.y - a.y);
		i64 dz = std::abs(b.z - a.z);
		return dx + dy + dz;
	}

	i64 manhattan_distance(ivec3 p1, ivec3 p2) noexcept
	{
		i64 x = p1.x - p2.x;
		i64 y = p1.y - p2.y;
		i64 z = p1.z - p2.z;
		return x * x + y * y + z * z;
	}

	ivec3 max(const ivec3 &a, const ivec3 &b) noexcept { return a > b ? a : b; }

	ivec3 min(const ivec3 &a, const ivec3 &b) noexcept { return a < b ? a : b; }

	// vec4
	using ivec4 = glm::vec<4, i64, glm::defaultp>;
	using ivec3 = glm::vec<3, i64, glm::defaultp>;
	using ivec2 = glm::vec<2, i64, glm::defaultp>;

	// line
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

	std::optional<ivec2> intersect(const ivec2 &a, const ivec2 &b, const ivec2 &c, const ivec2 &d) noexcept
	{

		// Line AB represented as a1x + b1y = c1
		i64 a1 = b.y - a.y;
		i64 b1 = a.x - b.x;
		i64 c1 = a1 * (a.x) + b1 * (a.y);

		// Line CD represented as a2x + b2y = c2
		i64 a2 = d.y - c.y;
		i64 b2 = c.x - d.x;
		i64 c2 = a2 * (c.x) + b2 * (c.y);

		i64 determinant = a1 * b2 - a2 * b1;

		if (determinant == 0)
			return {};

		i64 x = (b2 * c1 - b1 * c2) / determinant;
		i64 y = (a1 * c2 - a2 * c1) / determinant;

		return ivec2{x, y};
	}

	std::optional<ivec2> intersect(const line &a, const line &b) noexcept { return intersect(a.p1, a.p2, b.p1, b.p2); }

#endif
}
