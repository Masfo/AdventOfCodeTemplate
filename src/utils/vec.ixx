export module aoc.vec;
import std;
import aoc.debug;
import aoc.types;

template<std::integral T = i64>
T modulus(T x, T N) noexcept
{
	if (N == T{0})
		return 0;
	return (x % N + N) % N;
}

template<typename Data, size_t size>
concept HasEnoughData = requires(Data data) { data.size() >= size; };

export template<typename T, std::size_t length>
requires(std::integral<T> or std::floating_point<T>) and (length > 1)
struct vec final
{

	std::array<T, length> m_data{{0}};

	using vec_type = vec<T, length>;
	using type     = T;

	vec() = default;

	vec(T v) noexcept { m_data.fill(v); }

	vec(T x, T y) noexcept
	requires(length >= 2)
	{
		m_data[0] = x;
		m_data[1] = y;
	}

	vec(T x, T y, T z) noexcept
	requires(length >= 3)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	vec(T x, T y, T z, T w) noexcept
	requires(length >= 4)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
		m_data[3] = w;
	}

	vec(const std::initializer_list<T> list, const std::source_location& loc = std::source_location::current()) noexcept
	{
		dbgln_if(list.size() > length,
				 "{}({}): Warning: initializer list (length: {}) is longer than the container (length: {}).",
				 loc.file_name(),
				 loc.line(),
				 list.size(),
				 length);

		std::copy_n(list.begin(), length, m_data.begin());
	}

	constexpr operator vec_type() const noexcept
	{
		vec_type result = {};
		result.m_data   = m_data;
		return result;
	}

	constexpr void set_min() noexcept { m_data.fill(std::numeric_limits<T>::min()); }

	constexpr void set_max() noexcept { m_data.fill(std::numeric_limits<T>::max()); }

	constexpr void set_zero() noexcept { m_data.fill(T{0}); };

	constexpr T& at(size_t index) noexcept { return m_data[index]; }

	constexpr const T& at(size_t index) const noexcept { return m_data[index]; }

	constexpr T& operator[](size_t index) noexcept { return m_data[index]; }

	constexpr const T& operator[](size_t index) const noexcept { return m_data[index]; }

	constexpr vec_type& rotate_cw() noexcept
	requires(length == 2)
	{
		*this = vec_type{-m_data[1], m_data[0]};
		return *this;
	}

	constexpr vec_type& rotate_cw(const vec_type& origin) noexcept
	requires(length == 2)
	{
		*this = vec_type{
			-(m_data[1] - origin[1]) + origin[0], //
			(m_data[0] - origin[0]) + origin[1]   //
		};
		return *this;
	}

	// assign
	// constexpr vec_type& operator=(const vec_type& other) = default;
	//
	// constexpr vec_type operator=(const vec_type other) = default;

	// add
	constexpr vec_type& operator+=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < length; ++i)
		{
			m_data[i] += other[i];
		}
		return *this;
	}

	constexpr vec_type operator+(const vec_type& other) const noexcept
	{
		vec_type result = *this;
		result += other;
		return result;
	}

	// sub
	constexpr vec_type& operator-=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < length; ++i)
		{
			m_data[i] -= other[i];
		}
		return *this;
	}

	constexpr vec_type operator-(const vec_type& other) const noexcept
	{
		vec_type result = *this;
		result -= other;
		return result;
	}

	// mul
	constexpr vec_type& operator*=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < length; ++i)
		{
			m_data[i] *= other[i];
		}
		return *this;
	}

	constexpr vec_type operator*(const vec_type& other) const noexcept
	{
		vec_type result = *this;
		result *= other;
		return result;
	}

	constexpr vec_type& operator/=(const vec_type& other) noexcept
	{
		if (other.has_zero())
		{
			panic("vec<{}>: {} / 0 - divide by zero", *this, length);
			std::unreachable();
		}

		for (size_t i = 0; i < length; ++i)
			m_data[i] /= other[i];

		return *this;
	}

	constexpr vec_type operator/(const vec_type& other) const noexcept
	{
		if (other.has_zero())
		{
			panic("vec<{}>: {} / 0 - divide by zero", *this, length);
			std::unreachable();
		}

		vec_type result = *this;
		for (size_t i = 0; i < length; ++i)
			result[i] /= other[i];

		return result;
	}

	template<std::integral T>
	constexpr vec_type operator/(const T& scalar) const noexcept
	{
		if (scalar == 0)
		{
			panic("vec<{}>: {} / 0 - divide by zero", *this, length);
			std::unreachable();
		}

		vec_type result = *this;

		for (size_t i = 0; i < length; ++i)
			result[i] /= scalar;

		return result;
	}

	// unary
	constexpr vec_type& operator-() const noexcept { return *this * vec_type(-1); }

	constexpr vec_type& operator+() const noexcept { return *this; }

	// compare
	constexpr bool operator==(const vec_type& other) const noexcept
	{
		for (size_t i = 0; i < length; ++i)
		{
			if (m_data[i] != other[i])
				return false;
		}
		return true;
	}

	// compare
	constexpr auto operator<=>(const vec_type& other) const noexcept = default;

	// methods
	[[nodiscard("Use the minimum value")]] constexpr vec_type min(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::min(m_data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the maximum value")]] constexpr vec_type max(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::max(m_data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the absolute value")]] constexpr vec_type abs() const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::abs(m_data[i]);

		return result;
	}

	template<typename U = T>
	[[nodiscard("Use the distance value")]] constexpr U distance(const vec_type& other) const noexcept
	{
		U result{};
		for (size_t i = 0; i < length; ++i)
			result += as<U>(std::abs(m_data[i] - other[i]));
		return result;
	}

	[[nodiscard("Use the clamped value")]] constexpr vec_type clamp(const vec_type& cmin, const vec_type& cmax) const noexcept
	{

		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::clamp(m_data[i], cmin[i], cmax[i]);

		return result;
	}

	template<typename U = T>
	[[nodiscard("Use the sum value")]] constexpr U sum() const noexcept
	{
		U result{};
		for (size_t i = 0; i < length; ++i)
			result += as<U>(m_data[i]);
		return result;
	}

	template<typename U = T>
	[[nodiscard("Use the product value")]] constexpr U product() const noexcept
	{
		U result{m_data[0]};
		for (size_t i = 1; i < length; ++i)
			result *= as<U>(m_data[i]);
		return result;
	}

	[[nodiscard("Use the mod value")]] constexpr vec_type mod(const vec_type& other) const noexcept
	requires(length > 1)
	{
		vec_type result;
		for (size_t i = 0; i < length; ++i)
			result[i] = modulus(m_data[i], other[i]);

		return result;
	}

	// has_zero()
	bool has_zero() const noexcept
	{

		for (int i = 0; i < length; ++i)
			if (m_data[i] == 0)
				return true;
		return false;
	};

	// xyzw
	[[nodiscard("Use the x-coordinate")]] T x() const noexcept

	{
		static_assert(length >= 1, "Cant view x-axis. No data");
		return m_data[0];
	};

	[[nodiscard("Use the y-coordinate")]] T y() const noexcept
	{
		static_assert(length >= 2, "Cant view y-axis. No such data.");

		return m_data[1];
	};

	[[nodiscard("Use the z-coordinate")]] T z() const noexcept
	{
		static_assert(length >= 3, "Cant view z-axis. No such data.");

		return m_data[2];
	};

	[[nodiscard("Use the w-coordinate")]] T w() const noexcept
	{
		static_assert(length >= 4, "Cant view w-axis. No such data.");

		return m_data[3];
	};

	// rgba
	[[nodiscard("Use the red-channel")]] T r() const noexcept
	{
		static_assert(length >= 1, "Cant view red-channel. No such data.");
		return x();
	}

	[[nodiscard("Use the green-channel")]] T g() const noexcept
	{
		static_assert(length >= 2, "Cant view green-channel. No such data.");
		return y();
	}

	[[nodiscard("Use the blue-channel")]] T b() const noexcept
	{
		static_assert(length >= 3, "Cant view blue-channel. No such data.");
		return z();
	}

	[[nodiscard("Use the alpha-channel")]] T a() const noexcept
	{
		static_assert(length >= 4, "Cant view alpha-channel. No such data.");
		return w();
	}
};

export
{

	using ivec2 = vec<i64, 2>;
	using ivec3 = vec<i64, 3>;
	using ivec4 = vec<i64, 4>;

	using uvec2 = vec<u64, 2>;
	using uvec3 = vec<u64, 3>;
	using uvec4 = vec<u64, 4>;

	using rgb = vec<u8, 3>;

	const ivec2 MAX_IVEC2(MAX_I64);
	const ivec2 MIN_IVEC2(MIN_I64);
	const ivec2 ZERO_IVEC2(0);
	const ivec2 ivec2_zero(0, 0);

	const ivec3 MAX_IVEC3(MAX_I64);
	const ivec3 MIN_IVEC3(MIN_I64);
	const ivec3 ZERO_IVEC3(0);

	// index2d
	template<size_t WIDTH, size_t HEIGHT, std::integral T = i64>
	std::optional<T> index2D(const Indexable auto& container, const ivec2& v)
	{
		auto index = index2D<T, WIDTH, HEIGHT>(v[0], v[1]);
		if (not index)
			return {};

		return container[*index];
	}

	// std::ranges::sort(points, grid_order());
	// aka reading order (left->right, top->bottom)
	struct grid_order
	{
		inline bool operator()(const ivec2& v1, const ivec2& v2) const
		{
			//
			return (v1[1] < v2[1]) || (v1[1] == v2[1] && v1[0] < v2[0]);
		}
	};

	struct grid_order_reverse
	{
		inline bool operator()(const ivec2& v1, const ivec2& v2) const
		{
			//
			return (v1[1] > v2[1]) || (v1[1] == v2[1] && v1[0] > v2[0]);
		}
	};

	struct ivec2_hash
	{
		size_t operator()(const ivec2& k) const { return hash_values(k[0], k[1]); }
	};

	template<typename T, size_t len>
	[[nodiscard("Use the minimum value")]] constexpr vec<T, len> min(const vec<T, len>& lhs, const vec<T, len>& rhs)
	{
		return lhs.min(rhs);
	}

	template<typename T, size_t len>
	[[nodiscard("Use the maximum value")]] constexpr vec<T, len> max(const vec<T, len>& lhs, const vec<T, len>& rhs)
	{
		return lhs.max(rhs);
	}

	template<typename T, size_t len>
	[[nodiscard("Use the absolute value")]] constexpr vec<T, len> abs(const vec<T, len>& lhs)
	{
		return lhs.abs();
	}

	template<typename T = i64, typename U = T, size_t len>
	[[nodiscard("Use the distance value")]] constexpr T distance(const vec<U, len>& lhs, const vec<U, len>& rhs)
	{
		return lhs.distance<T>(rhs);
	}

	template<typename T, size_t len>
	[[nodiscard("Use the clamped value")]] constexpr vec<T, len> clamp(
		const vec<T, len>& v, const vec<T, len>& cmin, const vec<T, len>& cmax)
	{
		return v.clamp(cmin, cmax);
	}

	template<typename T = i64, typename U = T, size_t len>
	[[nodiscard("Use the sum value")]] constexpr T sum(const vec<T, len>& v)
	{
		return v.sum<T>();
	}

	template<typename T = i64, typename U = T, size_t len>
	[[nodiscard("Use the product value")]] constexpr T product(const vec<T, len>& v)
	{
		return v.product<T>();
	}

	// Helpers
	auto generate_cube_faces(const ivec3 origin) noexcept -> std::vector<ivec3>
	{
		std::vector<ivec3> ret;
		ret.reserve(6);
		ret.push_back(ivec3{origin[0] + 1, origin[1], origin[2]});
		ret.push_back(ivec3{origin[0] - 1, origin[1], origin[2]});

		ret.push_back(ivec3{origin[0], origin[1] + 1, origin[2]});
		ret.push_back(ivec3{origin[0], origin[1] - 1, origin[2]});

		ret.push_back(ivec3{origin[0], origin[1], origin[2] + 1});
		ret.push_back(ivec3{origin[0], origin[1], origin[2] - 1});
		return ret;
	}

	auto generate_cube_offset(const ivec3 origin) noexcept -> std::vector<ivec3>
	{
		std::vector<ivec3> ret;
		ret.reserve(26);
		for (int x = -1; x <= 1; ++x)
			for (int y = -1; y <= 1; ++y)
				for (int z = -1; z <= 1; ++z)
					if (!(x == 0 && y == 0 && z == 0))
						ret.emplace_back(ivec3{origin[0] + x, origin[1] + y, origin[2] + z});
		return ret;
	}

	auto generate_hypercube_offset(const ivec4 origin) noexcept -> std::vector<ivec4>
	{
		std::vector<ivec4> ret;
		ret.reserve(80);
		for (int x = -1; x <= 1; ++x)
			for (int y = -1; y <= 1; ++y)
				for (int z = -1; z <= 1; ++z)
					for (int w = -1; w <= 1; ++w)
						if (!(x == 0 && y == 0 && z == 0 && w == 0))
							ret.emplace_back(ivec4{origin[0] + x, origin[1] + y, origin[2] + z, origin[4] + w});
		return ret;
	}

	// Cuboid
	struct cuboid
	{
		cuboid() = default;

		cuboid(const ivec3& min, const ivec3& max, int on)
			: min(min)
			, max(max)
			, on(on)
		{
		}

		ivec3 min, max;
		int   on{-1};

		u64 volume() const { return (1ull + max[0] - min[0]) * (1ull + max[1] - min[1]) * (1ull + max[2] - min[2]); }

		std::optional<cuboid> intersects(const cuboid& b) const
		{
			if (min[0] > b.max[0] || max[0] < b.min[0] || min[1] > b.max[1] || max[1] < b.min[1] || min[2] > b.max[2] || max[2] < b.min[2])
				return {};

			return cuboid{{std::max(min[0], b.min[0]), std::max(min[1], b.min[1]), std::max(min[2], b.min[2])},
						  {std::min(max[0], b.max[0]), std::min(max[1], b.max[1]), std::min(max[2], b.max[2])},
						  -b.on};
		}
	};
}

// STD specials
export namespace std
{

	template<>
	struct hash<ivec2>
	{
		size_t operator()(const ivec2& value) const { return hash_values(value[0], value[1]); }
	};

	// ivec3
	template<>
	struct hash<ivec3>
	{
		size_t operator()(const ivec3& value) const { return hash_values(value[0], value[1], value[2]); }
	};

	// ivec4
	template<>
	struct hash<ivec4>
	{
		size_t operator()(const ivec4& value) const { return hash_values(value[0], value[1], value[2], value[3]); }
	};

	template<typename T, size_t len>
	struct formatter<vec<T, len>>

	{
		constexpr auto parse(std::format_parse_context& ctx) { return ctx.begin(); }

		auto format(const vec<T, len>& vec, std::format_context& ctx) const
		{
			std::format_to(ctx.out(), "[");
			for (size_t i = 0; i < len; ++i)
				std::format_to(ctx.out(), "{}{}", vec[i], i < len - 1 ? "," : "");

			return std::format_to(ctx.out(), "]");
		}
	};

} // namespace std
