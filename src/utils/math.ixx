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

		irange(T f, T l)
			: first(f)
			, last(l)
		{
		}

		inline auto empty() const { return irange<T>{std::numeric_limits<T>::max(), std::numeric_limits<T>::min()}; }

		[[nodiscard]] bool is_empty() const { return first > last; };

		[[nodiscard]] bool intersects(const irange &r) const
		{
			return !r.is_empty() && (contains(r.first) || contains(r.last) || r.contains(first) || r.contains(last));
		}

		[[nodiscard]] auto width() const { return is_empty() ? T{} : last - first + 1; };

		[[nodiscard]] bool contains(T v) const { return v >= first && v <= last; };

		[[nodiscard]] bool contains(const irange &other) const noexcept { return (other.first >= first && other.last <= last); }

		// intersection
		[[nodiscard]] auto intersection(const irange &r) const noexcept
		{
			if (is_empty() || r.is_empty())
				return empty();
			if (!intersects(r))
				return empty();

			return irange{std::max(first, r.first), std::min(last, r.last)};
		}

		[[nodiscard]] inline auto operator&(const irange &r) const { return intersection(r); }

		// merged/union
		[[nodiscard]] auto merge(const irange &r) const noexcept
		{
			if (is_empty())
				return r;
			if (r.is_empty())
				return *this;

			return irange{std::min(first, r.first), std::max(last, r.last)};
		}

		// merge/union
		[[nodiscard]] inline auto operator+(const irange &r) const { return merge(r); }

		// contains one-way
		[[nodiscard]] inline auto operator&=(const irange &r) const { return contains(r); }

		// intersects one-way
		[[nodiscard]] inline auto operator|=(const irange &r) const { return intersects(r); }

		// contains both
		inline bool operator&&(const irange &r) const { return contains(r) || r.contains(*this); };

		// intersects both
		inline bool operator||(const irange &r) const { return intersects(r) || r.intersects(*this); };

		bool operator==(const irange &other) const = default;

		auto operator<(const irange &other) const noexcept
		{
			if (first < other.first)
				return true;
			if (first == other.first)
			{
				if (last < other.last)
					return true;
			}
			return false;
		}

		T first{};
		T last{};
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

	template<std::integral T = i64>
	T mod(T x, T N) noexcept
	{
		if (N == T{0})
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

	/*
			f32 x1  = p1[0];
			f32 y1  = p1[1];
			f32 dx1 = v1[0];
			f32 dy1 = v1[1];

			f32 x2  = p2[0];
			f32 y2  = p2[1];
			f32 dx2 = v2[0];
			f32 dy2 = v2[1];

			f32 m1 = dy1 / dx1;
			f32 m2 = dy2 / dx2;


			f32 fe = std::abs(m2 - m1);
			if (std::abs(m2 - m1) < f32_epsilon)
				continue;

			f32 x = (m1 * x1 - m2 * x2 + y2 - y1) / (m1 - m2);
			f32 y = (m1 * m2 * (x2 - x1) + m2 * y1 - m1 * y2) / (m2 - m1);

			##

				const s64 minC = 200'000'000'000'000;
				const s64 maxC = 400'000'000'000'000;
				s32 intersect = 0;
				for (s32 i = 0; i < stones.Count(); i++)
				{
				  for (s32 j = i + 1; j < stones.Count(); j++)
				  {
					auto &si = stones[i];
					auto &sj = stones[j];

					double cx = double(si.pos.x);
					double cy = double(si.pos.y);
					double dx = double(si.vel.x);
					double dy = double(si.vel.y);

					double ax = double(sj.pos.x);
					double ay = double(sj.pos.y);
					double bx = double(sj.vel.x);
					double by = double(sj.vel.y);

					double det = (dx*by - dy*bx);
					if (det == 0)
					  { continue; }

					double u = (bx*(cy-ay) + by*(ax-cx))/det;
					double t = (dx*(cy-ay) + dy*(ax-cx))/det;

					double x = ax + bx * t;
					double y = ay + by * t;

					if (u < 0 || t < 0)
					  { continue; }

					if (x >= double(minC) && x <= double(maxC) && y >= double(minC) && y <= double(maxC))
					  { intersect++; }
				  }
				}



//#############
		[[nodiscard]] auto line() const {
            auto x0 = position(0);
            auto x1 = velocity(0) + x0;

            auto y0 = position(1);
            auto y1 = velocity(1) + y0;

            auto m = static_cast<double>(y1-y0) / (x1-x0);
            auto b = y0-m*x0;
            return std::pair{m, b};
        }

        [[nodiscard]] auto crossed_in_the_future(Eigen::Vector2d v) const {
            return std::signbit(v(0) - position(0)) == std::signbit(velocity(0)) &&
                   std::signbit(v(1) - position(1)) == std::signbit(velocity(1));
        }

	*/

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

	std::optional<f64vec2> intersect2d(const f64vec2 &a, const f64vec2 &b, const f64vec2 &c, const f64vec2 &d) noexcept
	{

		// Line AB represented as a1x + b1y = c1
		f64 a1 = b.y() - a.y();
		f64 b1 = a.x() - b.x();
		f64 c1 = a1 * (a.x()) + b1 * (a.y());

		// Line CD represented as a2x + b2y = c2
		f64 a2 = d.y() - c.y();
		f64 b2 = c.x() - d.x();
		f64 c2 = a2 * (c.x()) + b2 * (c.y());

		f64 determinant = a1 * b2 - a2 * b1;

		if (determinant == 0)
			return std::nullopt;

		f64 x = (b2 * c1 - b1 * c2) / determinant;
		f64 y = (a1 * c2 - a2 * c1) / determinant;

		return f64vec2(x, y);
	}

	std::optional<ivec2> intersect2d(const ivec2 &a, const ivec2 &b, const ivec2 &c, const ivec2 &d) noexcept
	{
		const f64vec2 fa(static_cast<f64>(a[0]), static_cast<f64>(a[1]));
		const f64vec2 fb(static_cast<f64>(b[0]), static_cast<f64>(b[1]));
		const f64vec2 fc(static_cast<f64>(c[0]), static_cast<f64>(c[1]));
		const f64vec2 fd(static_cast<f64>(d[0]), static_cast<f64>(d[1]));

		auto r = intersect2d(fa, fb, fc, fd);
		if (r)
		{
			auto rb = *r;
			return ivec2(static_cast<ivec2::type>(rb[0]), static_cast<ivec2::type>(rb[1]));
		}
		return {};
	}

	std::optional<ivec2> intersect2d(const line &a, const line &b) noexcept { return intersect2d(a.p1, a.p2, b.p1, b.p2); }

	/*
	https://stackoverflow.com/questions/2316490/the-algorithm-to-find-the-point-of-intersection-of-two-3d-line-segment


	std::optional<point3d> intersection(const point& lhs, const point& rhs)
	{
		const auto p0 = lhs.position;
		const auto p1 = lhs.position+lhs.velocity;
		const auto p2 = rhs.position;
		const auto p3 = rhs.position+rhs.velocity;

		const double t0_num = (p0.x-p2.x)*(p2.y-p3.y) - (p0.y-p2.y)*(p2.x-p3.x);
		const double den = (p0.x-p1.x)*(p2.y-p3.y) - (p0.y-p1.y)*(p2.x-p3.x);

		if(den==0)
			return std::nullopt;

		const double t1_num = (p0.x-p2.x)*(p0.y-p1.y) - (p0.y-p2.y)*(p0.x-p1.x);

		const auto t0 = t0_num/den;
		const auto t1 = t1_num/den;

		if(t0<0 || t1<0)
			return std::nullopt;

		return point3d(lhs.position.x + lhs.velocity.x*t0, lhs.position.y+lhs.velocity.y*t0,0);
	}

	*/
}
