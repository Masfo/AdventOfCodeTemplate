
export module aoc.stringhelper;

import aoc.debug;
import aoc.types;
import aoc.math;
import aoc.vec;
import std;

export
{
	constexpr std::string_view digit_string{"0123456789"};
	constexpr std::string_view whitespace_string{" \t\f\n\r\v"};
	constexpr std::string_view lowercase_string{"abcdefghijklmnopqrstuvwxyz"};
	constexpr std::string_view uppercase_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	constexpr std::string_view alphabet_string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
	constexpr std::string_view alphanum_string{"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

	enum class ignore : u32
	{
		lowercase    = 1 << 0,
		uppercase    = 1 << 1,
		whitespace   = 1 << 2,
		digits       = 1 << 3,
		alphanumeric = 1 << 4,
		alphabet     = lowercase | uppercase,
		whitealpha   = whitespace | alphabet,

		none = 0 << 0,
		n    = none,
		l    = lowercase,
		u    = uppercase,
		a    = l | u,
		w    = whitespace,
		d    = digits,
		wa   = w | a,
		an   = lowercase | uppercase | digits,
	};

	constexpr inline ignore operator~(ignore a) { return static_cast<ignore>(~static_cast<std::underlying_type<ignore>::type>(a)); }

	constexpr inline ignore operator|(ignore a, ignore b)
	{
		return static_cast<ignore>(static_cast<std::underlying_type<ignore>::type>(a) | static_cast<std::underlying_type<ignore>::type>(b));
	}

	constexpr inline ignore operator&(ignore a, ignore b)
	{
		return static_cast<ignore>(static_cast<std::underlying_type<ignore>::type>(a) & static_cast<std::underlying_type<ignore>::type>(b));
	}

	constexpr inline ignore operator^(ignore a, ignore b)
	{
		return static_cast<ignore>(static_cast<std::underlying_type<ignore>::type>(a) ^ static_cast<std::underlying_type<ignore>::type>(b));
	}

	constexpr inline ignore &operator|=(ignore &a, ignore b)
	{
		a = a | b;
		return a;
	}

	constexpr inline ignore operator&=(ignore &a, ignore b)
	{
		a = a & b;
		return a;
	}

	constexpr inline ignore &operator^=(ignore &a, ignore b)
	{
		a = a ^ b;
		return a;
	}

	std::string input(std::string_view ask)
	{
		std::string ret;
		std::print("{}", ask);
		std::getline(std::cin, ret);
		return ret;
	}

	std::string      strip(std::string_view str, std::string_view strip_chars) noexcept;
	std::string      strip(std::string_view str, ignore option) noexcept;
	std::string_view trim(std::string_view s) noexcept;

	template<typename T = char>
	bool isrange(T c, T a, T b) noexcept
	{
		return (c >= a) && (c <= b);
	}

	template<typename T = char>
	bool isdigit(T c) noexcept
	{
		return isrange(c, '0', '9');
	}

	template<typename T = char>
	bool isascii(T c) noexcept
	{
		return isrange(c, 'a', 'z') or isrange(c, 'A', 'Z');
	}

	template<typename T = i64>
	inline char constexpr to_char(T value, int base = 10)
	{
		return to_string(value, base)[0];
	}

	// try_to_number
	template<typename T = i64>
	inline std::optional<T> try_to_number(std::string_view str, int base = 10)
	{
		if (str.empty())
			return {};

		T val{};
		if (str[0] == '#')
		{
			str.remove_prefix(1);
			auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), val, 16)};
			if (ec == std::errc())
				return val;
			trace("try_to_number(\"{}\", base({})). Is not a hex number", str, 16);
			return {};
		}

		if (str[0] == '+')
			str.remove_prefix(1);

		auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), val, base)};
		if (ec == std::errc())
			return val;

		trace("try_to_number(\"{}\", base({})). Is not a number", str, base);
		return {};
	}

	// to_number
	template<typename T = i64>
	inline T constexpr to_number(std::string_view str, int base = 10)
	{

		if (auto result = try_to_number<T>(str, base); result)
			return *result;
		else
			panic("to_number(\"{}\"): failed to convert to number", str);
		return T{0};
	}

	template<typename T = i64>
	inline T constexpr to_number(char c, [[maybe_unused]] int base = 10)
	{
		return to_number(std::string_view{&c}, base);
	}

	// convert_to_vector
	template<typename T>
	auto convert_to_vector(std::string_view str)
	{
		if constexpr (std::is_integral_v<T>)
		{
			return split<T>(str, " ");
		}
		else
		{
			static_assert(true, "Not implemented");
		}
	}

	// convert to set
	template<typename T>
	auto convert_to_set(std::string_view str)
	{
		if constexpr (std::is_integral_v<T>)
		{
			std::set<T> ret;
			const auto  s = split<T>(str, " ");
			for (const auto &i : s)
				ret.insert(i);
			return ret;
		}
		else
		{
			static_assert(true, "Not implemented");
		}
	}

	template<typename T>
	constexpr bool is_optional = false;

	template<typename T>
	constexpr bool is_optional<std::optional<T>> = true;

	template<typename Type>
	Type convert_to_type(std::string_view str)
	{
		if constexpr (std::is_same_v<Type, std::string_view>)
			return str.data();
		else if constexpr (std::is_convertible_v<Type, std::string>)
			return static_cast<Type>(str);
		else if constexpr (std::is_same_v<Type, char>)
			return str[0];
		else if constexpr (std::is_integral_v<Type> || std::is_floating_point_v<Type>)
			return to_number<Type>(trim(str));
		else if constexpr (std::is_same_v<Type, ivec4>)
		{
			static_assert(true, "Not implemented");
		}
		else if constexpr (std::is_same_v<Type, std::vector<i64>>)
		{
			return convert_to_vector<i64>(str);
		}
		else if constexpr (std::is_same_v<Type, std::set<i64>>)
		{
			return convert_to_set<i64>(str);
		}
		else if constexpr (is_optional<Type>)
		{
			using T = Type::value_type;
			if constexpr (std::is_same_v<T, char>)
				return std::optional<char>(str[0]);
			else if constexpr (std::is_integral_v<T> or std::is_floating_point_v<T>)
				return try_to_number<T>(str);
			else
				return std::optional<T>(str);
		}
		else
		{
			static_assert(true, "Not implemented");
		}
	}

	// count
	i64 count(auto str, std::string_view interests) noexcept
	{
		return std::ranges::count_if(str, [&interests](char c) { return interests.contains(c); });
	}

	// contains
	bool contains(std::string_view input, std::string_view check) { return input.contains(check); }

	// replace
	std::string replace(std::string & subject, const std::string_view search, std::string_view replace) noexcept
	{
		size_t pos = 0;
		while ((pos = subject.find(search, pos)) != std::string::npos)
		{
			subject.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return subject;
	}

	std::string replace(std::string_view subject, const std::string_view search, std::string_view replace) noexcept
	{
		std::string output(subject);
		size_t      pos = 0;
		while ((pos = output.find(search, pos)) != std::string::npos)
		{
			output.replace(pos, search.length(), replace);
			pos += replace.length();
		}
		return output;
	}

	std::string strip(std::string_view str, char a, char z) noexcept
	{
		std::string ret;
		ret.reserve(str.size());
		for (const char &c : str)
			if (c < a || c > z)
				ret += c;

		return ret;
	}

	std::string strip(std::string_view str, std::string_view strip_chars) noexcept
	{
		std::string ret;
		ret.reserve(str.size());

		for (auto &c : str)
			if (!strip_chars.contains(c))
				ret += c;

		return ret;
	}

	std::string strip(std::string_view str, ignore option) noexcept
	{
		using enum ignore;
		std::string newstr{str};

		if (option == none)
			return newstr;

		if ((option & whitespace) == whitespace)
			newstr = strip(newstr, '\0', ' ');

		if ((option & lowercase) == lowercase)
			newstr = strip(newstr, 'a', 'z');

		if ((option & uppercase) == uppercase)
			newstr = strip(newstr, 'A', 'Z');

		if ((option & digits) == digits)
			newstr = strip(newstr, '0', '9');

		return newstr;
	}

	std::string_view trim_front(std::string_view s) noexcept
	{
		if (s.empty())
			return s;

		s.remove_prefix(s.find_first_not_of(whitespace_string));
		return s;
	}

	std::string_view trim_back(std::string_view s) noexcept
	{
		if (s.empty())
			return s;

		s.remove_suffix(s.size() - s.find_last_not_of(whitespace_string) - 1);
		return s;
	}

	std::string_view trim(std::string_view s) noexcept
	{
		s = trim_front(s);
		return trim_back(s);
	};

	std::string trim_copy(const std::string &s) noexcept
	{
		std::string ret = s;
		ret             = trim_front(ret);
		ret             = trim_back(ret);
		return ret;
	};

	std::vector<std::string> trim(const std::vector<std::string> &from) noexcept
	{
		std::vector<std::string> ret;
		ret.reserve(from.size());
		for (const auto &i : from)
			ret.emplace_back(trim(i));
		return ret;
	}

	inline auto trim_transform = [](std::string_view str) -> std::string_view { return trim(str); };

	// ###############################################

	// ###############################################

	std::string reverse_copy(const std::string &str) noexcept
	{
		std::string ret = str;
		std::reverse(ret.begin(), ret.end());
		return ret;
	}

	std::vector<std::string> rotate_cw(const std::vector<std::string> &vec) noexcept
	{
		std::vector<std::string> ret(vec.size());
		size_t                   width = 0;
		for (const auto &v : vec)
			width = std::max(width, v.size());
		ret.resize(width);

		for (const auto &line : vec)
		{
			size_t y = 0;
			for (const auto &c : line)
				ret[y++].push_back(c);
		}
		return ret;
	}

	std::vector<std::string> rotate_cw(const std::vector<std::string_view> vec) noexcept
	{
		std::vector<std::string> ret(vec.size());
		size_t                   width = 0;
		for (const auto &v : vec)
			width = std::max(width, v.size());
		ret.resize(width);

		for (const auto &line : vec)
		{
			size_t y = 0;
			for (const auto &c : line)
				ret[y++].push_back(c);
		}
		return ret;
	}

	std::vector<std::string> pass(const std::vector<std::string> &vec) noexcept { return vec; }

	std::vector<std::string_view> pass(const std::vector<std::string_view> vec) noexcept { return vec; }

	// ################################
	// to

	template<typename T, typename... Ts>
	using AllSame = std::enable_if_t<std::conjunction_v<std::is_same<T, Ts>...>>;

	template<typename T, typename U, typename... Us>
	auto concat(const U first, const Us... args)->T
	{

		if constexpr (sizeof...(args) > 0 && std::is_same_v<T, std::string>)
		{
			std::vector<U> a{first, args...};
			return std::ranges::fold_left(a, std::string(""), std::plus{});
		}
		else if constexpr (std::is_integral_v<T> && std::is_convertible_v<U, std::string>)
		{
			std::vector<U> a{first, args...};

			return to_number<T>(std::ranges::fold_left(a, std::string(""), std::plus{}));
		}
		else if constexpr (std::is_integral_v<T> && std::is_integral_v<U>)
		{
			std::vector<U>           a{first, args...};
			std::vector<std::string> b;

			for (const auto &i : a)
				b.emplace_back(std::to_string(i));

			auto cc = std::ranges::fold_left(b, std::string(""), std::plus{});

			return to_number<T>(cc);
		}
		else if constexpr (sizeof...(args) == 0 && std::is_integral_v<T> && std::is_same_v<U, std::vector<std::string>>)
		{
			static_assert(sizeof...(args) == 0, "Only one parameter please");

			std::vector<std::string> ret;
			for (const auto &i : first)
				ret.emplace_back(i);
			std::string cc = std::ranges::fold_left(ret, std::string(""), std::plus{});

			return to_number<T>(cc);
		}
		else if constexpr (sizeof...(args) == 0 && std::is_same_v<T, i64> && std::is_same_v<U, std::vector<i64>>)
		{

			std::vector<std::string> ret;
			for (const auto &i : first)
				ret.emplace_back(std::to_string(i));
			auto cc = std::ranges::fold_left(ret, std::string(""), std::plus{});
			return to_number<T>(cc);
		}
		else if constexpr (sizeof...(args) == 0, std::is_same_v<T, std::string> && std::is_same_v<U, std::vector<std::string>>)
		{
			return std::ranges::fold_left(first, std::string(""), std::plus{});
		}
		else if constexpr (sizeof...(args) == 0, std::is_same_v<T, std::string> && std::is_same_v<U, std::vector<i64>>)
		{
			std::vector<std::string> ret;
			for (const auto &i : first)
				ret.emplace_back(std::to_string(i));
			return std::ranges::fold_left(ret, std::string(""), std::plus{});
		}
		else if constexpr (sizeof...(args) == 0, std::is_same_v<T, std::vector<i64>> && std::is_same_v<U, std::vector<i64>>)
		{
			std::vector<i64>         ret;
			std::vector<std::string> a;

			for (const auto &i : first)
				a.emplace_back(std::to_string(i));

			std::string cc = std::ranges::fold_left(a, std::string(""), std::plus{});

			ret.emplace_back(to_number(cc));

			return ret;
		}
		else
		{
			static_assert(true, "Not implemented");
			std::unreachable();
		}
	}

	template<typename T = i64, typename... Args>
	auto to_vec(const Args... args)
	{
		std::vector<T> ret{args...};

		return ret;
	}

	std::set<char> to_set(std::string_view str) noexcept { return {str.begin(), str.end()}; }

	std::unordered_set<char> to_unordered_set(std::string_view str) noexcept { return {str.begin(), str.end()}; }

	std::deque<char> to_deque(std::string_view str) noexcept { return {str.begin(), str.end()}; }

	i64 to_i64(std::string_view str) noexcept { return to_number<i64>(str); }

	u64 to_u64(std::string_view str) noexcept { return to_number<u64>(str); }

	i32 to_i32(std::string_view str) noexcept { return to_number<i32>(str); }

	u32 to_u32(std::string_view str) noexcept { return to_number<u32>(str); }

	std::string string_intersection(std::string a, std::string b) noexcept
	{
		std::ranges::sort(a);
		std::ranges::sort(b);
		std::string ret;
		std::ranges::set_intersection(a, b, std::back_inserter(ret));
		return ret;
	}

	std::string string_difference(std::string a, std::string b) noexcept
	{
		std::ranges::sort(a);
		std::ranges::sort(b);
		std::string ret;
		std::ranges::set_difference(a, b, std::back_inserter(ret));
		return ret;
	}

	// #####################################
	// ranges

	inline auto is_whitespace = [](char c) { return whitespace_string.contains(c); };
	inline auto empty         = [](const auto str) { return not str.empty(); };
	inline auto empty_string  = [](const std::string str, const auto &) { return not str.empty(); };

	auto newlines = [](auto x, auto y) { return not(x == "\n" && y == "\n"); };

	auto newline = [](char x, char) { return not(x == '\n'); };

	inline auto trim_front_view = std::views::drop_while(is_whitespace);
	inline auto trim_back_view  = std::views::reverse | trim_front_view | std::views::reverse;
	inline auto trim_view       = trim_front_view | trim_back_view;
	inline auto view_to_string  = std::ranges::to<std::string>();

	template<typename T>
	inline auto to_vector = std::ranges::to<std::vector<T>>();

	inline auto chunk_by_empty    = std::views::chunk_by(empty_string);
	inline auto chunk_by_newlines = std::views::chunk_by(newlines);
	inline auto chunk_by_newline  = std::views::chunk_by(newline);

	inline auto filter_empty = std::views::filter(empty);

	// try_to
	template<typename T = i64>
	requires(std::integral<T> || std::floating_point<T>)
	auto try_to = std::views::transform([](std::string_view x) { return try_to_number<T>(x); });

	// to
	template<typename T = i64, T DefaultValue = T{}>
	requires(std::integral<T> || std::floating_point<T>)
	auto to = std::views::transform(
		[](std::string_view x) -> T
		{
			auto v = try_to_number<T>(x);
			return v ? *v : DefaultValue;
		});
}

// STD specials
export namespace std
{

} // namespace std
