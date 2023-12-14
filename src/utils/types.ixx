module;

export module aoc.types;

import std;
import aoc.debug;
export
{
	using i64 = std::int64_t;
	using u64 = std::uint64_t;
	using i32 = std::int32_t;
	using u32 = std::uint32_t;
	using i16 = std::int16_t;
	using u16 = std::uint16_t;
	using i8  = std::int8_t;
	using u8  = std::uint8_t;

	using f32 = float;
	using f64 = double;

	constexpr u64 MAX_U64 = std::numeric_limits<u64>::max();
	constexpr u64 MIN_U64 = std::numeric_limits<u64>::min();
	constexpr i64 MIN_I64 = std::numeric_limits<i64>::min();
	constexpr i64 MAX_I64 = std::numeric_limits<i64>::max();

	constexpr u32 MAX_U32 = std::numeric_limits<u32>::max();
	constexpr u32 MIN_U32 = std::numeric_limits<u32>::min();
	constexpr i32 MIN_I32 = std::numeric_limits<i32>::min();
	constexpr i32 MAX_I32 = std::numeric_limits<i32>::max();

	constexpr u8 MAX_U8 = std::numeric_limits<u8>::max();
	constexpr u8 MIN_U8 = std::numeric_limits<u8>::min();
	constexpr i8 MIN_I8 = std::numeric_limits<i8>::min();
	constexpr i8 MAX_I8 = std::numeric_limits<i8>::max();

	template<typename T>
	using undirected_graph = std::unordered_map<T, std::unordered_set<T>>;

	template<typename T>
	struct Node
	{
		T   value{};
		int weight{};
	};

	template<typename T>
	using directed_graph = std::unordered_map<Node<T>, std::unordered_set<Node<T>>>;

	template<typename T = i64>
	struct answer
	{
		T part1{};
		T part2{};
	};

	template<typename... Ts>
	struct overload : Ts...
	{
		using Ts::operator()...;
	};
	template<class... Ts>
	overload(Ts...) -> overload<Ts...>;

	// make_array
	template<class... Ts>
	constexpr std::array<typename std::decay<typename std::common_type<Ts...>::type>::type, sizeof...(Ts)> make_array(Ts && ...ts)
	{
		return std::array<typename std::decay<typename std::common_type<Ts...>::type>::type, sizeof...(Ts)>{std::forward<Ts>(ts)...};
	}

	template<typename T, typename U>
	T as(U value)
	{
		if constexpr (std::is_same_v<T, U>)
			return value;
		else
		{
			if ((static_cast<T>(value) <= static_cast<U>(std::numeric_limits<T>::max())) &&
				(static_cast<T>(value) > static_cast<U>(std::numeric_limits<T>::min())))
			{
				return static_cast<T>(value);
			}
			else
			{
				assert_msg(false,
						   std::format("Could not convert value '{}' safely. Target can only hold {}...{}. Trying to fit {}",
									   value,
									   std::numeric_limits<T>::min(),
									   std::numeric_limits<T>::max(),
									   value));

				return std::numeric_limits<T>::max();
			}
		}
	}

	template<typename T>
	i64 as_i64(T t)
	{
		return as<i64>(t);
	}

	// hash
	template<typename T>
	void hash_combine(std::size_t & seed, const T &val)
	{
		seed ^= std::hash<T>()(val) + 0x9e37'79b9 + (seed << 6) + (seed >> 2);
	}

	template<typename T, typename... Types>
	void hash_combine(std::size_t & seed, const T &val, const Types &...args)
	{
		hash_combine(seed, val);
		hash_combine(seed, args...);
	}
	void hash_combine(std::size_t &) { }

	template<typename... Types>
	std::size_t hash_val(const Types &...args)
	{
		std::size_t seed = 0;
		hash_combine(seed, args...);
		return seed;
	}

	// vmax
	template<typename A, typename B, typename... Rest>
	constexpr auto vmax(const A &a, const B &b, const Rest &...rest)
	{
		if constexpr (sizeof...(rest) == 0)
		{
			return std::max(a, b);
		}
		else
		{
			return vmax(vmax(a, b), rest...);
		}
	}

	// vmin
	template<typename A, typename B, typename... Rest>
	constexpr auto vmin(const A &a, const B &b, const Rest &...rest)
	{
		if constexpr (sizeof...(rest) == 0)
		{
			return std::min(a, b);
		}
		else
		{
			return vmin(vmin(a, b), rest...);
		}
	}

	// vmod

	template<class T>
	concept Indexable = requires(T container) {
		container[0];
		container.size();
	};

	template<std::integral T, size_t WIDTH, size_t HEIGHT>
	std::optional<T> index2D(T x, T y)
	{
		static_assert(WIDTH > 0, "Width must be positive");
		static_assert(HEIGHT > 0, "Height must be positive");

		if (x < 0 || y < 0 || x >= WIDTH || y >= HEIGHT)
			return {};

		return y * WIDTH + x;
	}

	template<std::integral T, size_t WIDTH, size_t HEIGHT, size_t DEPTH>
	std::optional<T> index3D(T x, T y, T z)
	{
		static_assert(WIDTH > 0, "Width must be positive");
		static_assert(HEIGHT > 0, "Height must be positive");
		static_assert(DEPTH > 0, "DEPTH must be positive");

		if (x < 0 || y < 0 || z < 0 || x >= WIDTH || y >= HEIGHT || z >= DEPTH)
			return {};

		return (z * WIDTH * HEIGHT) + (y * HEIGHT) + x;
	}

	// from index: x: index % width
	//             y: index / width

	/*
	struct S
	{
		std::string first;
		std::string last;
		bool operator==(const S&) const = default; // since C++20
	};

	struct MyHash
	{
		std::size_t operator()(const S& s) const noexcept
		{
			std::size_t result = 0;
			hash_combine(result, s.first);
			hash_combine(result, s.last);
			return result;
		}
	};

	// std specialization
	namespace std
	{
	template <>
	struct hash<S>
	{
		std::size_t operator()(const S& c) const
		{
			std::size_t result = 0;
			hash_combine(result, s.first);
			hash_combine(result, s.last);
			return result;
		}
	};
	}



	struct MyType
	{
		float float_x;
		std::string my_string
	};

	// note: value. (dot)
	IMPLEMENT_STD_HASH(MyType, value.float_x, value.my_string);



#define STD_HASH(T, ...) \
	namespace std \
	{ \
		template <> struct hash<T> \
		{ \
			size_t operator()(const T &value) const \
			{ \
				i64 result = 0; \
				hash_combine(result, __VA_ARGS__); \
				return result; \
			} \
		}; \
	}



	*/
}
