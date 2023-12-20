module;
#pragma once

export module aoc.math;
import std;
import aoc.types;
import aoc.vec;

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

	template<typename T>
	bool between(T v, T vmin, T vmax) noexcept
	{
		return (v >= vmin) && (v <= vmax);
	}

	template<typename T = i64>
	struct irange
	{
		irange() = default;

		irange(T s, T e)
			: min(s)
			, max(e)
		{
		}

		inline auto empty() const { return irange<T>{std::numeric_limits<T>::max(), std::numeric_limits<T>::min()}; }

		[[nodiscard]] bool is_empty() const { return min > max; };

		[[nodiscard]] bool intersects(const irange &r) const
		{
			return !r.is_empty() && (contains(r.min) || contains(r.max) || r.contains(min) || r.contains(max));
		}

		[[nodiscard]] auto width() const { return is_empty() ? T{} : max - min + 1; };

		[[nodiscard]] bool contains(T v) const { return min <= v && v <= max; };

		[[nodiscard]] bool contains(const irange &other) const noexcept { return (other.min >= min && other.max <= max); }

		// intersection
		[[nodiscard]] auto intersection(const irange &r) const noexcept
		{
			if (is_empty() || r.is_empty())
				return empty();
			if (!intersects(r))
				return empty();

			return irange{std::max(min, r.min), std::min(max, r.max)};
		}

		[[nodiscard]] inline auto operator&(const irange &r) const { return intersection(r); }

		// merged/union
		[[nodiscard]] auto merge(const irange &r) const noexcept
		{
			if (is_empty())
				return r;
			if (r.is_empty())
				return *this;

			return irange{std::min(min, r.min), std::max(max, r.max)};
		}

		[[nodiscard]] inline auto operator+(const irange &r) const { return merge(r); }

		// contains one-way
		[[nodiscard]] inline auto operator&=(const irange &r) const { return contains(r); }

		// intersects one-way
		[[nodiscard]] inline auto operator|=(const irange &r) const { return intersects(r); }

		// contains both
		inline bool operator&&(const irange &r) const { return contains(r) || r.contains(*this); };

		// intersects both
		inline bool operator||(const irange &r) const { return intersects(r) || r.intersects(*this); };

		T min{};
		T max{};
	};

	template<typename T = i64>
	[[nodiscard]] bool contains(const irange<T> &r1, const irange<T> &r2)
	{
		return r1 && r2;
	}

	template<typename T = i64>
	[[nodiscard]] bool intersects(const irange<T> &r1, const irange<T> &r2)
	{
		return r1 || r2;
	}

	// common
	template<typename T = i64>
	T pow(T base, T exponent) noexcept
	{
		T temp{};
		if (exponent == 0)
			return 1;

		temp = pow(base, exponent / 2);
		if ((exponent % 2) == 0)
			return temp * temp;
		else
			return base * temp * temp;
	}

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

	template<typename T = i64>
	T sum(const auto &container)
	{
		return std::ranges::fold_left(container, T{0}, std::plus{});
	}

	template<typename T = i64>
	T product(const auto &container)
	{
		return std::ranges::fold_left(container, T{1}, std::multiplies{});
	}

	bool between(i64 value, i64 a, i64 b) noexcept { return value >= a && value <= b; }

	template<std::integral T = i64>
	T distance(T a, T b) noexcept
	{
		return as<T>(std::abs(a) + std::abs(b));
	}

	// vmin
	template<class A, class... Args>
	inline constexpr A vmin(A a, A b, Args... args)
	{
		if constexpr (sizeof...(args) == 0)
			return std::min(a, b);
		else
			return vmin(vmin(a, b), args...);
	}

	// vmax
	template<class A, class... Args>
	inline constexpr A vmax(A a, A b, Args... args)
	{
		if constexpr (sizeof...(args) == 0)
			return std::max(a, b);
		else
			return vmax(vmax(a, b), args...);
	}

	// vlcm
	template<class A, class... Args>
	inline constexpr A vlcm(A a, A b, Args... args)
	{
		return std::lcm(std::lcm(a, b), args...);
	}

	// lcm
	template<typename T>
	inline constexpr T lcm_compute(const T a, const T b) noexcept
	{
		return abs(a * (b / gcd(a, b)));
	}

	// lcm
	template<typename T>
	T lcm(const std::vector<T> &vec) noexcept
	{
		T ret{1};
		for (const auto &i : vec)
			ret = std::lcm(ret, i);
		return ret;
	}

	// https://en.wikipedia.org/wiki/Category:Figurate_numbers

	template<typename T = i64>
	T triangular_number(T n)
	{
		return (n * (n + 1)) / 2;
	}

	template<typename T = i64>
	T square_number(T n)
	{
		return n * n;
	}

	template<typename T = i64>
	inline constexpr T hexagonal_number(T n) noexcept
	{
		// H(n) = 3n^2 - 3n + 1
		return (3 * n * n) - (3 * n) + 1;
	}

	template<typename T = i64>
	T heptagonal_number(T n)
	{
		return (n * (5 * n - 3)) / 2;
	}

	template<typename T = i64>
	T octagonal_number(T n)
	{
		return n * (3 * n - 2);
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

		return ivec2(x, y);
	}

	std::optional<ivec2> intersect(const line &a, const line &b) noexcept { return intersect(a.p1, a.p2, b.p1, b.p2); }
}
