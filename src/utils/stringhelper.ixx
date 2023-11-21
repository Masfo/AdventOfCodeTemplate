
export module aoc.stringhelper;

import aoc.debug;
import aoc.types;
import aoc.math;
import aoc.vec;
import std;

const static std::string_view digit_string{"0123456789"};
const static std::string_view whitespace_string{" \t\f\n\r\v"};
const static std::string_view lowercase_string{"abcdefghijklmnopqrstuvwxyz"};
const static std::string_view uppercase_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
const static std::string_view alphabet_string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
const static std::string_view alphanum_string{"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

export
{

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

	std::string strip(std::string_view str, std::string_view strip_chars) noexcept;
	std::string strip(std::string_view str, ignore option) noexcept;

	template<typename T = i64>
	inline T constexpr to_number(std::string_view str, int base = 10)
	{

		T val{};
		if (not str.empty() && str[0] == '+')
			str.remove_prefix(1);
		auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), val, base)};

		if (ec == std::errc())
		{
			return val;
		}
		else if (ec == std::errc::invalid_argument)
		{
			dbgln("to_number: Invalid argument '{}'", str);
			throw std::invalid_argument(std::format("Invalid argument: '{}'", str));
		}
		else if (ec == std::errc::result_out_of_range)
		{
			dbgln("to_number: out of range '{}'", str);
			throw std::out_of_range(std::format("Out of range: '{}'", str));
		}
		return {0};
	}

	template<typename T = i64>
	inline std::string constexpr to_string(T value, int base = 10)
	{
		std::string str;
		str.resize(20);

		auto [ptr, ec]{std::to_chars(str.data(), str.data() + str.size(), value, base)};

		if (ec == std::errc())
		{
			return str;
		}
		else if (ec == std::errc::invalid_argument)
		{
			dbgln("to_ascii: Invalid argument '{}'", str);
			throw std::invalid_argument(std::format("Invalid argument: '{}'", str));
		}
		else if (ec == std::errc::result_out_of_range)
		{
			dbgln("to_ascii: out of range '{}'", str);
			throw std::out_of_range(std::format("Out of range: '{}'", str));
		}
		return {0};
	}

	template<typename T = i64>
	inline char constexpr to_char(T value, int base = 10)
	{
		return to_string(value, base)[0];
	}

	template<typename T = i64>
	inline std::optional<T> try_to_number(std::string_view str, int base = 10)
	{
		if (str.empty())
			return {};

		T val{};
		if (!str.empty() && (str[0] == '+'))
			str.remove_prefix(1);

		auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), val, base)};
		if (ec == std::errc())
			return val;

		trace("try_to_number(\"{}\", base({})). Is not a number", str, base);
		return {};
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
			return to_number<Type>(str);
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
