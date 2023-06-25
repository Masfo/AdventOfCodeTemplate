module;

#include "standard.h"

export module types;
import standard;


export
{
	using i64 = std::int64_t;
	using u64 = std::uint64_t;
	using i32 = std::int32_t;
	using u32 = std::uint32_t;
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

	template<typename... Ts>
	struct overload : Ts...
	{
		using Ts::operator()...;
	};
	template<class... Ts>
	overload(Ts...) -> overload<Ts...>;

	template<typename T, typename U>
	T as(U u)
	{
		return static_cast<T>(u);
	}

	template<typename T>
	i64 as_i64(T t)
	{
		return as<i64>(t);
	}


	template<typename T>
	i64 hash_combine(i64 & seed, const T &value)
	{
		auto hasher = std::hash<T>{};
		seed ^= hasher(value) + 0x9e37'79b9 + (seed << 6) + (seed >> 2);
		return seed;
	}

	template<typename T, typename... Rest>
	i64 hash_combine(i64 & seed, const T &v, const Rest &...rest)
	{
		seed = hash_combine(seed, v);
		return hash_combine(seed, rest...);
	}


} // namespace aoc
