export module aoc.stringsplit;

import std;
import aoc.types;
import aoc.vec;
import aoc.math;
import aoc.debug;
import aoc.stringhelper;

using namespace std::string_literals;
export
{

	// Split
	std::vector<std::string> split(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		std::string new_str{strip(str, option)};

		auto start = new_str.find_first_not_of(delims, 0);
		auto stop  = new_str.find_first_of(delims, start);

		std::vector<std::string> tokens;
		while (std::string::npos != stop || std::string::npos != start)
		{
			tokens.emplace_back(trim(new_str.substr(start, stop - start)));

			start = new_str.find_first_not_of(delims, stop);
			stop  = new_str.find_first_of(delims, start);
		}
		return tokens;
	}

	auto split_once(std::string_view str, std::string_view delims, ignore option = ignore::none)
	{
		std::string new_str{strip(str, option)};

		size_t pos = new_str.find(delims);
		if (pos != std::string::npos)
		{
			return make_array(new_str.substr(0, pos), new_str.substr(pos + 1));
		}
		else
		{
			return make_array(new_str, ""s);
		}
	}

	auto split_whitespace(std::string_view str) { return split(str, whitespace_string, ignore::none); }

	template<typename T>
	std::vector<T> split_to_integer(std::string_view str, std::string_view delims, ignore option) noexcept;

	template<size_t N>
	auto split_n(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);
		if (s.size() != N)
		{
			dbgln("split_n: Delimiter split input '{}' to {} parts. Expected to get {} parts", str, s.size(), N);
			for (const auto &i : s)
				dbgln("{}'{}'", "  ", i);
			assert_msg(s.size() == N, "Invalid delimiter/strip character");
		}

		std::array<std::string, N> ret{};
		std::copy_n(s.begin(), N, ret.begin());

		return ret;
	}

	template<typename T, size_t N>
	auto split(const std::string_view str, const std::string_view delims = " ", ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);
		if (s.size() < N)
		{
			dbgln("split_n: Delimiter split input '{}' to {} parts. Expected to get {} parts", str, s.size(), N);
			for (const auto &i : s)
				dbgln("{}'{}'", "  ", i);
			assert_msg(s.size() == N, "Invalid delimiter/strip character");
		}

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
	auto split(const std::string_view str, const std::string_view delims = " ", ignore option = ignore::none)
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
		if constexpr (std::is_same_v<T1, ivec2> || std::is_same_v<T1, ivec3> || std::is_same_v<T1, ivec4>)
		{
			const auto s = split(str, delims, option);
			T1         t1;
			T2         t2;

			const auto si = split<T1::type>(str, delims, option);

			if constexpr (std::is_same_v<T1, ivec2>)
			{
				t1 = T1(si[0], si[1]);
				t2 = convert_to_type<T2>(s[2]);
			}
			else if constexpr (std::is_same_v<T1, ivec3>)
			{
				t1 = T1(si[0], si[1], si[2]);
				t2 = convert_to_type<T2>(s[3]);
			}
			else if constexpr (std::is_same_v<T1, ivec4>)
			{
				t1 = T1(si[0], si[1], si[2], si[3]);
				t2 = convert_to_type<T2>(s[4]);
			}
			else
			{
				static_assert(true, "Not implemented");
			}

			return std::make_tuple(t1, t2);
		}
		else
		{
			const auto [c1, c2] = split_n<2>(str, delims, option);

			T1 t1 = convert_to_type<T1>(c1);
			T2 t2 = convert_to_type<T2>(c2);

			return std::make_tuple(t1, t2);
		}
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

	// ## With index 1
	template<typename T>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);

		if (I1 >= s.size())
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I1,
				  s.size() - 1);
			panic();
		}

		T t1 = convert_to_type<T>(s[I1]);

		return t1;
	}

	// ## With index 2
	template<typename T>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size())
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  std::max(I1, I2),
				  s.size() - 1);
			panic();
		}

		T t1 = convert_to_type<T>(trim(s[I1]));
		T t2 = convert_to_type<T>(trim(s[I2]));

		return std::make_tuple(t1, t2);
	}

	// ## With index 3
	template<typename T>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size())
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  I3,
				  vmax(I1, I2, I3),
				  s.size() - 1);
			panic();
		}

		T t1 = convert_to_type<T>(s[I1]);
		T t2 = convert_to_type<T>(s[I2]);
		T t3 = convert_to_type<T>(s[I3]);

		return std::make_tuple(t1, t2, t3);
	}

	// ## With index 4
	template<typename T>
	auto split(
		const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, size_t I4, ignore option = ignore::none)
	{
		const auto s = split(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size() || I4 >= s.size())
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{},{},{}): Tried to index beyond what was splitted. "
				  "Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  I3,
				  I4,
				  vmax(I1, I2, I3, I4),
				  s.size() - 1);
			panic();
		}

		T t1 = convert_to_type<T>(s[I1]);
		T t2 = convert_to_type<T>(s[I2]);
		T t3 = convert_to_type<T>(s[I3]);
		T t4 = convert_to_type<T>(s[I4]);

		return std::make_tuple(t1, t2, t3, t4);
	}

	// ## With index
	template<typename T1, typename T2>
	auto split(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, ignore option = ignore::none)
	{
		const auto s = split_n<2>(str, delims, option);

		if (I1 >= s.size() || I2 >= s.size())
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  std::max(I1, I2),
				  s.size() - 1);
			panic();
		}

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
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{},{}): Tried to index beyond what was splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  I3,
				  vmax(I1, I2, I3),
				  s.size() - 1);
			panic();
		}

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
		{
			trace("split<T1,T2>(\"{}\", \"{}\", {},{},{},{}): Tried to index beyond what was splitted. "
				  "Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  I3,
				  I4,
				  vmax(I1, I2, I3, I4),
				  s.size() - 1);
			panic();
		}

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

	// split_optional
	template<typename T1>
	auto split_optional(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};

		if (s.size() >= 1)
			t1 = convert_to_type<T1>(s[0]);

		return t1;
	}

	template<typename T1, typename T2>
	auto split_optional(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};
		std::optional<T2> t2{};

		if (s.size() >= 1)
			t1 = convert_to_type<T1>(s[0]);
		if (s.size() >= 2)
			t2 = convert_to_type<T2>(s[1]);

		return std::make_tuple(t1, t2);
	}

	template<typename T1, typename T2, typename T3>
	auto split_optional(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		const auto s = split(str, delims, option);

		std::optional<T1> t1{};
		std::optional<T2> t2{};
		std::optional<T3> t3{};

		if (s.size() >= 1)
			t1 = convert_to_type<T1>(s[0]);
		if (s.size() >= 2)
			t2 = convert_to_type<T2>(s[1]);
		if (s.size() >= 3)
			t3 = convert_to_type<T2>(s[2]);

		return std::make_tuple(t1, t2, t3);
	}

	template<typename T1, typename T2, typename T3, typename T4>
	auto split_optional(const std::string_view str, const std::string_view delims = "\n", ignore option = ignore::none) noexcept
	{
		const auto s = split(str, delims, option);

		std::optional<T1> t1{};
		std::optional<T2> t2{};
		std::optional<T3> t3{};
		std::optional<T3> t4{};

		if (s.size() >= 1)
			t1 = convert_to_type<T1>(s[0]);
		if (s.size() >= 2)
			t2 = convert_to_type<T2>(s[1]);
		if (s.size() >= 3)
			t3 = convert_to_type<T2>(s[2]);
		if (s.size() >= 4)
			t4 = convert_to_type<T2>(s[3]);

		return std::make_tuple(t1, t2, t3, t4);
	}

	// Split optional index
	// auto [op, value] = split_optional<char, i64>(str, " ", <index>, <index>);

	template<typename T1>
	auto split_optional(const std::string_view str, const std::string_view delims, size_t I1, ignore option = ignore::none) noexcept
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};

		if (I1 >= s.size())
		{
			trace("split_optional<T1,T2>(\"{}\", \"{}\", {}): Tried to index beyond what was splitted. Tried to index {} with maximum "
				  "of {}",
				  str,
				  delims,
				  I1,
				  I1,
				  s.size() - 1);
		}

		if (s.size() >= 1)
			t1 = convert_to_type<std::optional<T1>>(s[I1]);

		return t1;
	}

	template<typename T1, typename T2>
	auto split_optional(const std::string_view str, const std::string_view delims, size_t I1, size_t I2, ignore option = ignore::none)
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};
		std::optional<T2> t2{};

		if (I1 >= s.size() || I2 >= s.size())
		{
			trace("split_optional<T1,T2>(\"{}\", \"{}\", {},{}): Tried to index beyond what was splitted. "
				  "Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  std::max(I1, I2),
				  s.size() - 1);
		}

		if (s.size() >= 1)
			t1 = convert_to_type<std::optional<T1>>(s[I1]);
		if (s.size() >= 2)
			t2 = convert_to_type<std::optional<T2>>(s[I2]);

		return std::make_tuple(t1, t2);
	}

	template<typename T1, typename T2, typename T3>
	auto split_optional(
		const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, ignore option = ignore::none)
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};
		std::optional<T2> t2{};
		std::optional<T3> t3{};

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size())
		{
			trace("split_optional<T1,T2>(\"{}\", \"{}\", {},{},{}): Tried to index beyond what was splitted. "
				  "Tried to index {} with maximum of {}",
				  str,
				  delims,
				  I1,
				  I2,
				  I3,
				  vmax(I1, I2, I3),
				  s.size() - 1);
		}

		if (s.size() >= 1)
			t1 = convert_to_type<std::optional<T1>>(s[I1]);
		if (s.size() >= 2)
			t2 = convert_to_type<std::optional<T2>>(s[I2]);
		if (s.size() >= 3)
			t3 = convert_to_type<std::optional<T3>>(s[I3]);

		return std::make_tuple(t1, t2, t3);
	}

	template<typename T1, typename T2, typename T3, typename T4>
	auto split_optional(
		const std::string_view str, const std::string_view delims, size_t I1, size_t I2, size_t I3, size_t I4, ignore option = ignore::none)
	{
		const auto        s = split(str, delims, option);
		std::optional<T1> t1{};
		std::optional<T2> t2{};
		std::optional<T3> t3{};
		std::optional<T4> t4{};

		if (I1 >= s.size() || I2 >= s.size() || I3 >= s.size() || I4 >= s.size())
		{
			trace("split_optional<T1,T2>(\"{}\", \"{}\", {},{},{},{}): Tried to index beyond what was "
				  "splitted. Tried to index {} with maximum of {}",
				  str,
				  delims,

				  I1,
				  I2,
				  I3,
				  I4,
				  vmax(I1, I2, I3),
				  s.size() - 1);
		}

		if (s.size() >= 1)
			t1 = convert_to_type<std::optional<T1>>(s[I1]);
		if (s.size() >= 2)
			t2 = convert_to_type<std::optional<T2>>(s[I2]);
		if (s.size() >= 3)
			t3 = convert_to_type<std::optional<T3>>(s[I3]);
		if (s.size() >= 4)
			t4 = convert_to_type<std::optional<T3>>(s[I4]);

		return std::make_tuple(t1, t2, t3, t4);
	}

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

	// *********************************
	// //
	// split_to
	// void split_to_helper(const std::vector<std::string> &, int) { }

	template<typename T>
	std::tuple<T> split_to_helper(const std::vector<std::string> &splits, int index)
	{
		const T first = convert_to_type<T>(splits[index]);
		auto    ret   = std::make_tuple(first);
		return ret;
	}

	// auto [f1, f2] = split_to<i64, i64>("123 | 456", "|");
	// 	auto k = split_to<i64, std::string, i64>("123 | hello | 987", "|");

	template<typename T, typename... Rest>
	std::tuple<T, Rest...> split_to_helper(const std::vector<std::string> &splits, int index = 0)
	{
		auto first = std::make_tuple<T>(convert_to_type<T>(splits[index]));

		auto ret = std::tuple_cat(first, split_to_helper<Rest...>(splits, index + 1));

		// auto ret   = std::tuple_cat<T, Rest...>(first, std::tuple_cat(split_to_helper<Rest...>(splits, index + 1)));

		// split_to_helper<Rest...>(splits, index+1)
		//
		// auto ret = std::tuple_cat(std::make_tuple(T{}), split_to_helper<Rest...>(splits));
		return ret;
	}

	template<typename T, typename... Rest>
	auto split_to(std::string_view str, std::string_view delims = "\n", ignore option = ignore::none)
	{
		int pack_size = 1 + sizeof...(Rest);

		std::string new_str{strip(str, option)};

		const auto s = split(new_str, delims, option);

		if (pack_size != s.size())
		{
			dbgln("Delimiter \"{}\" split input \"{}\" to {} parts. You gave {} types. Must be same size.\nSplit parts:\n",
				  delims,
				  str,
				  s.size(),
				  pack_size);
			for (const auto &[idx, l] : s | std::views::enumerate)
				dbgln("{}. \"{}\"", idx, l);
			dbgln("");

			throw std::range_error(std::format(
				"Delimiter '{}' split input to {} parts. You wanted {} types to split to. Must be same size", delims, s.size(), pack_size));
		}
		if constexpr (sizeof...(Rest) > 0)
			return split_to_helper<T, Rest...>(s);
		else
			return split_to_helper<T>(s);
	}
}
