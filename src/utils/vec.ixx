export module aoc.vec;
import std;
import aoc.debug;
import aoc.types;

template<typename T, size_t len>
struct vec
{
	static constexpr std::size_t length = len;
	using vec_type                      = vec<T, len>;

	vec() = default;

	vec(T value)
	{
		assert_index(1);
		data[0] = x;
	}

	vec(T x, T y)
	{
		assert_index(2);
		data[0] = x;
		data[1] = y;
	}

	vec(T x, T y, T z)
	{
		assert_index(3);
		data[0] = x;
		data[1] = y;
		data[2] = z;
	}

	vec(std::initializer_list<T> list)
	{

		assert_msg(list.size() <= len, "Too big initializer list");
		std::copy(list.begin(), list.end(), data.begin());
		//
	}

	constexpr operator vec_type() const noexcept
	{
		vec_type result = {};
		result.data     = data;
		return result;
	}

	constexpr T& at(size_t index) noexcept
	{
		assert_index(index);

		return data[index];
	}

	constexpr const T& at(size_t index) const noexcept
	{
		assert_index(index);

		return data[index];
	}

	constexpr T& operator[](size_t index) noexcept
	{
		assert_index(index);

		return data[index];
	}

	constexpr const T& operator[](size_t index) const noexcept
	{
		assert_index(index);

		return data[index];
	}

	// add
	constexpr vec_type& operator+=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < other.length; ++i)
		{
			data[i] += other[i];
		}
		return *this;
	}

	constexpr vec_type& operator+(const vec_type& other) noexcept
	{
		vec_type result = *this;
		result += other;
		return result;
	}

	// sub
	constexpr vec_type& operator-=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < other.length; ++i)
		{
			data[i] -= other[i];
		}
		return *this;
	}

	constexpr vec_type& operator-(const vec_type& other) noexcept
	{
		vec_type result = *this;
		result -= other;
		return result;
	}

	// mul
	constexpr vec_type& operator*=(const vec_type& other) noexcept
	{
		for (size_t i = 0; i < other.length; ++i)
		{
			data[i] *= other[i];
		}
		return *this;
	}

	constexpr vec_type& operator*(const vec_type& other) noexcept
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
			data[i] /= other[i];
		}
		return *this;
	}

	constexpr vec_type& operator/(const vec_type& other) noexcept
	{
		vec_type result = *this;
		result /= other;
		return result;
	}

	// unary
	constexpr vec_type& operator-() { return *this * -1; }

	constexpr vec_type& operator+() { return *this; }

	//


	// compare
	constexpr bool operator==(const vec_type& other) const noexcept
	{
		for (size_t i = 0; i < other.length; ++i)
		{
			if (data[i] != other[i])
				return true;
		}
		return false;
	}

	auto operator<=>(const vec_type&) const = default;

	// methods
	[[nodiscard("Use the minimum value")]] constexpr vec_type& min(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < other.length; ++i)
			result[i] = std::min(data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the maximum value")]] constexpr vec_type& max(const vec_type& other) const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < other.length; ++i)
			result[i] = std::max(data[i], other[i]);

		return result;
	}

	[[nodiscard("Use the absolute value")]] constexpr vec_type& abs() const noexcept
	{
		vec_type result{0};
		for (size_t i = 0; i < length; ++i)
			result[i] = std::abs(data[i]);

		return result;
	}

	template<typename U = T>
	constexpr U distance(const vec_type& other) const noexcept
	{
		T result{};
		for (size_t i = 0; i < length; ++i)
			result += std::abs(data[i] - other[i]);
		return as<U>(result);
	}

	[[nodiscard("Use the coordinate")]] T x() const noexcept
	{
		assert_index(0);
		return data[0];
	};

	[[nodiscard("Use the coordinate")]] T y() const noexcept
	{
		assert_index(1);
		return data[1];
	};

	[[nodiscard("Use the coordinate")]] T z() const noexcept
	{
		assert_index(2);
		return data[2];
	};

	[[nodiscard("Use the coordinate")]] T w() const noexcept
	{
		assert_index(3);
		return data[3];
	};

	std::array<T, length> data{{0}};

private:
	constexpr void assert_index(size_t index) const noexcept
	{
		assert_msg(index <= length, "Not valid index");
		dbgln_if(index > length, "Out of bounds for index {}", index);
	}
};

export
{
	using ivec2 = vec<i64, 2>;
	using ivec3 = vec<i64, 3>;
	using ivec4 = vec<i64, 4>;


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
}

namespace std
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
			//
			std::format_to(ctx.out(), "[");
			for (size_t i = 0; i < len; ++i)
				std::format_to(ctx.out(), "{}{}", vec[i], i < len - 1 ? "," : "");

			return std::format_to(ctx.out(), "]");
		}
	};

} // namespace std
