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
		trace("Are you sure you want to add just a single value?");
		data.fill(value);
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
		assert_msg(index <= length, "Index larger than array");
		return data[index];
	}

	constexpr const T& at(size_t index) const noexcept
	{
		assert_msg(index <= length, "Index larger than array");
		return data[index];
	}

	constexpr T& operator[](size_t index) noexcept
	{
		assert_msg(index <= length, "Index larger than array");
		return data[index];
	}

	constexpr const T& operator[](size_t index) const noexcept
	{
		assert_msg(index <= length, "Index larger than array");
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

	std::array<T, length> data{{0}};
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

} // namespace aoc

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
} // namespace std
