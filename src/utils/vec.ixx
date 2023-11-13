export module aoc.vec;
import std;
import aoc.debug;
import aoc.types;

template<typename Data, size_t size>
concept HasEnoughData = requires(Data data) { data.size() >= size; };

export template<typename T, std::size_t length>
requires(std::integral<T> or std::floating_point<T>) and (length > 1)
struct vec
{
	std::array<T, length> m_data{{0}};

	using vec_type = vec<T, length>;

	vec() = default;

	explicit vec(T v) noexcept { m_data.fill(v); }

	explicit vec(T x, T y) noexcept
	requires(length >= 2)
	{
		m_data[0] = x;
		m_data[1] = y;
	}

	explicit vec(T x, T y, T z) noexcept
	requires(length >= 3)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
	}

	explicit vec(T x, T y, T z, T w) noexcept
	requires(length >= 4)
	{
		m_data[0] = x;
		m_data[1] = y;
		m_data[2] = z;
		m_data[3] = w;
	}

	explicit vec(std::initializer_list<T> list, const std::source_location& loc = std::source_location::current()) noexcept
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

	constexpr T& at(size_t index) noexcept { return m_data[index]; }

	constexpr const T& at(size_t index) const noexcept { return m_data[index]; }

	constexpr T& operator[](size_t index) noexcept { return m_data[index]; }

	constexpr const T& operator[](size_t index) const noexcept { return m_data[index]; }

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

	constexpr vec_type& operator+(const vec_type& other) const noexcept
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

	constexpr vec_type& operator-(const vec_type& other) const noexcept
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

	constexpr vec_type& operator*(const vec_type& other) const noexcept
	{
		vec_type result = *this;
		result *= other;
		return result;
	}

	// div
	constexpr vec_type& operator/=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < other.length; ++i)
		{
			m_data[i] /= other[i];
		}
		return *this;
	}

	constexpr vec_type& operator/(const vec_type& other) const noexcept
	{
		vec_type result = *this;
		result /= other;
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

	auto operator<=>(const vec_type&) const = default;

	// methods
	[[nodiscard("Use the minimum value")]] constexpr vec_type& min(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::min(m_data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the maximum value")]] constexpr vec_type& max(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::max(m_data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the absolute value")]] constexpr vec_type& abs() const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::abs(m_data[i]);

		return result;
	}

	template<typename U = T>
	constexpr U distance(const vec_type& other) const noexcept
	{
		T result{};
		for (size_t i = 0; i < length; ++i)
			result += std::abs(m_data[i] - other[i]);
		return as<U>(result);
	}

	[[nodiscard("Use the coordinate")]] T x() const noexcept
	{
		static_assert(length >= 1, "Cant view x-axis. No data");
		return m_data[0];
	};

	[[nodiscard("Use the coordinate")]] T y() const noexcept
	{
		static_assert(length >= 2, "Cant view y-axis. No such data.");

		return m_data[1];
	};

	[[nodiscard("Use the coordinate")]] T z() const noexcept
	{
		static_assert(length >= 3, "Cant view z-axis. No such data.");

		return m_data[2];
	};

	[[nodiscard("Use the coordinate")]] T w() const noexcept
	{
		static_assert(length >= 4, "Cant view w-axis. No such data.");

		return m_data[3];
	};
};

export
{

	using ivec2 = vec<i64, 2>;
	using ivec3 = vec<i64, 3>;
	using ivec4 = vec<i64, 4>;

	using uvec2 = vec<u64, 2>;
	using uvec3 = vec<u64, 3>;
	using uvec4 = vec<u64, 4>;

	ivec2 MAX_IVEC2{MAX_I64, MAX_I64};
	ivec2 MIN_IVEC2{MIN_I64, MIN_I64};

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

	template<typename T, size_t len>
	[[nodiscard("Use the distance value")]] constexpr vec<T, len> distance(const vec<T, len>& lhs, const vec<T, len>& rhs)
	{
		return lhs.distance(rhs);
	}

#if 0
	// Scalar add
	template<typename T, typename U, size_t len>
	[[nodiscard("Use the added value")]] inline constexpr vec<T, len> operator+(const vec<T, len>& lhs, const U scalar)
	{
		return lhs + vec<T, len>(scalar);
	}

	template<typename T, typename U, size_t len>
	[[nodiscard("Use the added value")]] inline constexpr vec<T, len> operator+(const U scalar, const vec<T, len>& rhs)
	{
		return vec<T, len>(scalar) + rhs;
	}

	// Scalar sub
	template<typename T, typename U, size_t len>
	[[nodiscard("Use the subtracted value")]] inline constexpr vec<T, len> operator-(const vec<T, len>& lhs, const U scalar)
	{
		return lhs - vec<T, len>(scalar);
	}

	template<typename T, typename U, size_t len>
	[[nodiscard("Use the added value")]] inline constexpr vec<T, len> operator-(const U scalar, const vec<T, len>& rhs)
	{
		return vec<T, len>(scalar) - rhs;
	}

	// Scalar mul
	template<typename T, typename U, size_t len>
	[[nodiscard("Use the multiplied value")]] inline constexpr vec<T, len> operator*(const vec<T, len>& lhs, const U scalar)
	{
		return lhs * vec<T, len>(scalar);
	}

	template<typename T, typename U, size_t len>
	[[nodiscard("Use the multiplied value")]] inline constexpr vec<T, len> operator*(const U scalar, const vec<T, len>& rhs)
	{
		return vec<T, len>(scalar) * rhs;
	}

	// Scalar div
	template<typename T, typename U, size_t len>
	[[nodiscard("Use the divided value")]] inline constexpr vec<T, len> operator/(const vec<T, len>& lhs, const U scalar)
	{
		return lhs / vec<T, len>(scalar);
	}

	template<typename T, typename U, size_t len>
	[[nodiscard("Use the divided value")]] inline constexpr vec<T, len> operator/(const U scalar, const vec<T, len>& rhs)
	{
		return vec<T, len>(scalar) / rhs;
	}
#endif
}

// STD specials
export namespace std
{

	template<>
	struct hash<ivec2>
	{
		size_t operator()(const ivec2& value) const { return hash_val(value[0], value[1]); }
	};

	template<>
	struct hash<ivec3>
	{
		size_t operator()(const ivec3& value) const { return hash_val(value[0], value[1], value[2]); }
	};

	template<>
	struct hash<ivec4>
	{
		size_t operator()(const ivec4& value) const { return hash_val(value[0], value[1], value[2], value[3]); }
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
