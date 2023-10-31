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
	T distance(T a, T b) noexcept
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
		i64 a1 = b.y() - a.y();
		i64 b1 = a.x() - b.x();
		i64 c1 = a1 * (a.x()) + b1 * (a.y());

		// Line CD represented as a2x + b2y = c2
		i64 a2 = d.y() - c.y();
		i64 b2 = c.x() - d.x();
		i64 c2 = a2 * (c.x()) + b2 * (c.y());

		i64 determinant = a1 * b2 - a2 * b1;

		if (determinant == 0)
			return {};

		i64 x = (b2 * c1 - b1 * c2) / determinant;
		i64 y = (a1 * c2 - a2 * c1) / determinant;

		return ivec2{x, y};
	}

	std::optional<ivec2> intersect(const line &a, const line &b) noexcept { return intersect(a.p1, a.p2, b.p1, b.p2); }
}
