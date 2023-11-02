module;

export module aoc.stringhelper;

import aoc.debug;
import aoc.types;
import aoc.math;
import aoc.vec;
import std;

const static std::string digit_string{"0123456789"};
const static std::string whitespace_string{" \t\f\n\r\v"};
const static std::string lowercase_string{"abcdefghijklmnopqrstuvwxyz"};
const static std::string uppercase_string{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
const static std::string alphabet_string{"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};
const static std::string alphanum_string{"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"};

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

		none = 0 << 0,
		n    = none,
		l    = lowercase,
		u    = uppercase,
		a    = l | u,
		w    = whitespace,
		d    = digits,
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
	std::string strip(std::string_view str, std::string_view strip_chars) noexcept;
	std::string strip(std::string_view str, ignore option) noexcept;

	template<typename T = i64>
	inline T constexpr to_number(std::string_view str, int base = 10)
	{
		T val{};
		if (str[0] == '+')
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
	inline std::optional<T> try_to_number(std::string_view str, int base = 10)
	{
		T val{};
		if (!str.empty() && (str[0] == '+'))
			str.remove_prefix(1);

		auto [ptr, ec]{std::from_chars(str.data(), str.data() + str.size(), val, base)};
		if (ec == std::errc())
			return val;

		return std::nullopt;
	}

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
		else if constexpr (std::is_same_v<Type, std::optional<i64>>)
			return try_to_number<i64>(str);
		else if constexpr (std::is_same_v<Type, std::optional<char>>)
			return std::optional<char>(str[0]);
		else if constexpr (std::is_same_v<Type, std::optional<std::string>>)
			return std::optional<std::string>(str);
		else
		{
			static_assert(true, "Conversion not implemented");
		}
	}

	// Split
	std::vector<std::string> split(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		auto start = new_str.find_first_not_of(delims, 0);
		auto stop  = new_str.find_first_of(delims, start);

		std::vector<std::string> tokens;
		while (std::string::npos != stop || std::string::npos != start)
		{
			tokens.emplace_back(new_str.substr(start, stop - start));

			start = new_str.find_first_not_of(delims, stop);
			stop  = new_str.find_first_of(delims, start);
		}
		return tokens;
	}
	template<typename T>
	std::vector<T> split_to_integer(std::string_view str, std::string_view delims, ignore option) noexcept;

	template<size_t N>
	auto split_n(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);
		if (s.size() < N)
			throw std::range_error(std::format("Invalid delimiter/strip character, expected to get {} splits, got {}", N, s.size()));

		std::array<std::string, N> ret{};
		std::copy_n(s.begin(), N, ret.begin());

		return ret;
	}

	template<typename T, size_t N>
	auto split(const std::string_view str, const std::string_view delims, ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);
		if (s.size() < N)
			throw std::range_error(std::format("Invalid delimiter/strip character, expected to get {} splits, got {}", N, s.size()));

		if constexpr (N == 1)
			return convert_to_type<T>(s[0]);
		else if constexpr (N >= 2)
		{
			std::array<T, N> ret{};

			for (int i = 0; i < N; ++i)
				ret[i] = convert_to_type<T>(s[i]);

			return ret;
		}
	}

	template<typename T>
	auto split(const std::string_view str, const std::string_view delims, ignore option = ignore::none)
	{

		if constexpr (std::is_same_v<T, char>)
		{
			auto              s = split(str, delims, option);
			std::vector<char> ret;
			for (const auto &c : s)
				ret.push_back(c[0]);
			return ret;
		}
		else if constexpr (std::is_integral_v<T>)
		{
			return split_to_integer<T>(str, delims, option);
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			return split<std::string, 1>(str, delims, option);
		}
		else if constexpr (std::is_same_v<T, std::deque<i64>>)
		{
			auto            s = split_to_integer<i64>(str, delims, option);
			std::deque<i64> ret;
			ret.assign_range(s);
			return ret;
		}
		else if constexpr (std::is_same_v<T, std::deque<std::string>>)
		{
			auto                    s = split(str, delims, option);
			std::deque<std::string> ret;
			ret.assign_range(s);
			return s;
		}
		else if constexpr (std::is_same_v<T, ivec2>)
		{
			auto s = split<i64>(str, delims, option);
			return ivec2(s[0], s[1]);
		}
		else if constexpr (std::is_same_v<T, ivec3>)
		{
			auto s = split<i64>(str, delims, option);
			return ivec3(s[0], s[1], s[2]);
		}
		else if constexpr (std::is_same_v<T, ivec4>)
		{
			auto s = split<i64>(str, delims, option);
			return ivec4(s[0], s[1], s[2], s[3]);
		}
		else
		{
			static_assert(true, "split<T> - not implemented");
		}
	}

	template<typename T1, typename T2>
	auto split(const std::string_view str, const std::string_view delims, ignore option = ignore::none) noexcept
	{
		const auto [c1, c2] = split_n<2>(str, delims, option);

		T1 t1 = convert_to_type<T1>(c1);
		T2 t2 = convert_to_type<T2>(c2);

		return std::make_tuple(t1, t2);
	}

	template<typename T1, typename T2, typename T3>
	auto split(const std::string_view str, const std::string_view delims, ignore option = ignore::none) noexcept
	{
		const auto s = split_n<3>(str, delims, option);

		T1 t1 = convert_to_type<T1>(s[0]);
		T2 t2 = convert_to_type<T2>(s[1]);
		T3 t3 = convert_to_type<T3>(s[2]);

		return std::make_tuple(t1, t2, t3);
	}

	template<typename T1, typename T2, typename T3, typename T4>
	auto split(const std::string_view str, const std::string_view delims, ignore option = ignore::none) noexcept
	{
		const auto s = split_n<4>(str, delims, option);

		T1 t1 = convert_to_type<T1>(s[0]);
		T2 t2 = convert_to_type<T2>(s[1]);
		T3 t3 = convert_to_type<T3>(s[2]);
		T4 t4 = convert_to_type<T4>(s[2]);

		return std::make_tuple(t1, t2, t3, t4);
	}

	// ## With index
	template<typename T1, typename T2>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, ignore option = ignore::none)
	{
		const auto s = split_n<2>(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size())
			throw std::range_error(std::format(
				"split<T1,T2>(\"{}\", \"{}\", {},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				str,
				delims,
				I1,
				I2,
				std::max(I1, I2),
				s.size() - 1));

		T1 t1 = convert_to_type<T1>(s[I1]);
		T2 t2 = convert_to_type<T2>(s[I2]);

		return std::make_tuple(t1, t2);
	}

	// ## With index
	template<typename T1, typename T2, typename T3>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, ignore option = ignore::none)
	{
		const auto s = split_n<3>(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size())
			throw std::range_error(std::format(
				"split<T1,T2>(\"{}\", \"{}\", {},{},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				str,
				delims,
				I1,
				I2,
				I3,
				vmax(I1, I2, I3),
				s.size() - 1));

		T1 t1 = convert_to_type<T1>(s[I1]);
		T2 t2 = convert_to_type<T2>(s[I2]);
		T3 t3 = convert_to_type<T3>(s[I3]);

		return std::make_tuple(t1, t2, t3);
	}

	template<typename T1, typename T2, typename T3, typename T4>
	auto split(
		const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, size_t I4, ignore option = ignore::none)
	{
		const auto s = split_n<4>(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size() || I4 >= s.size())
			throw std::range_error(std::format(
				"split<T1,T2>(\"{}\", \"{}\", {},{},{},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				str,
				delims,
				I1,
				I2,
				I3,
				I4,
				vmax(I1, I2, I3, I4),
				s.size() - 1));

		T1 t1 = convert_to_type<T1>(s[I1]);
		T2 t2 = convert_to_type<T2>(s[I2]);
		T3 t3 = convert_to_type<T3>(s[I3]);
		T4 t4 = convert_to_type<T4>(s[I4]);

		return std::make_tuple(t1, t2, t3, t4);
	}

	template<typename T>
	std::vector<T> split_to_integer(std::string_view str, std::string_view delims, ignore option) noexcept
	{

		std::string new_str{strip(str, option)};

		std::vector<T>           ret;
		std::vector<std::string> s = split(new_str, delims);

		for (auto &word : s)
			ret.push_back(to_number<T>(word));
		return ret;
	}
	template<size_t count, typename T>
	auto split_to_integer(std::string_view str, std::string_view delims = " \t\n", ignore option = ignore::none) noexcept
		-> std::array<T, count>
	{
		std::string new_str{strip(str, option)};

		std::array<T, count> ret{};

		auto s = split<count>(new_str, delims);

		std::transform(s.begin(), s.begin() + count, ret.begin(), [](auto str) -> T { return to_number<T>(str); });

		return ret;
	}

	template<typename T = i64>
	std::vector<T> split_to_integers(const std::string_view str, const std::string_view delims, ignore option = ignore::none) noexcept
	{
		static_assert(std::is_integral_v<T>, "Only integral types");
		std::string new_str{strip(str, option)};

		auto start = new_str.find_first_not_of(delims, 0);
		auto stop  = new_str.find_first_of(delims, start);

		std::vector<T> tokens;
		while (std::string::npos != stop || std::string::npos != start)
		{
			tokens.emplace_back(to_number<T>(new_str.substr(start, stop - start)));
			start = new_str.find_first_not_of(delims, stop);
			stop  = new_str.find_first_of(delims, start);
		}
		return tokens;
	}

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

	std::string_view trim(const std::string_view s)
	{
		auto front = std::find_if_not(s.begin(), s.end(), [](int c) { return std::isspace(c); });
		auto back  = std::find_if_not(s.rbegin(), s.rend(), [](int c) { return std::isspace(c); }).base();
		return std::string_view(front, back);
	}

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

	// Split delimiter with it
	std::vector<std::string> split_keep(std::string_view str, const std::string_view delims, ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		std::vector<std::string> tokens;

		while (!new_str.empty())
		{
			auto start = new_str.find_first_not_of(delims, 0);
			auto stop  = new_str.find_first_of(delims, 0);
			if (start > stop)
				std::swap(start, stop);

			auto s = new_str.substr(0, stop - start);
			tokens.push_back(s);

			if (stop == std::string::npos || start == std::string::npos)
				break;

			new_str = new_str.substr(stop - start);
		}

		return tokens;
	}

	std::vector<std::string> split_exact(
		std::string_view str, std::string_view delims, bool include_empty, ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		std::vector<std::string> output;
		u64                      first = 0;
		while (first < new_str.size())
		{
			const auto second = new_str.find(delims, first);

			if (include_empty || first != second) // empty line
				output.emplace_back(new_str.substr(first, second - first));

			if (second == std::string_view::npos)
				break;
			first = second + delims.size();
		}
		return output;
	}

	std::vector<std::string> split_exact(const std::string_view str, u64 length, ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		std::vector<std::string> v;
		v.reserve(2);
		if (length <= new_str.length())
		{
			v.emplace_back(std::string(new_str.substr(0, length)));
			v.emplace_back(std::string(new_str.substr(length)));
		}
		return v;
	}

	std::vector<std::string> split_stride(std::string_view str, u64 stride, ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		std::vector<std::string> v;

		for (u64 i = 0; i <= str.length(); i += stride)
			v.emplace_back(str.substr(i, stride));

		return v;
	}

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

	std::string input(std::string_view ask)
	{
		std::string ret;
		std::print("{}", ask);
		std::getline(std::cin, ret);
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
}
