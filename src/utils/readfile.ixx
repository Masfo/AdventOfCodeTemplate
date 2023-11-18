module;

export module aoc.readfile;
import std;

import aoc.debug;
import aoc.types;
import aoc.stringhelper;
import aoc.stringsplit;

namespace fs = std::filesystem;

export enum class include_emptys {
	yes,
	no,
};

export
{
	std::vector<i64> read_lines_integers_delimiter(std::string_view, std::string_view);

	//
	// std::generator<std::string_view> read_lines(
	//	std::filesystem::path & file, std::string_View delims = "\n", include_emptys ie = include_emptys::no)
	//{
	//}

	std::string read_file(std::string_view filename)
	{
		try
		{
			if (!fs::exists(filename))
				throw fs::filesystem_error(std::format("File not found: {}\n", filename),
										   std::make_error_code(std::errc::no_such_file_or_directory));

			std::ifstream ifile(filename.data());
			std::string   str{(std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>()};

			return str;
		}
		catch (const std::filesystem::filesystem_error &e)
		{
			std::string w{strip(e.what(), "\n")};
			trace("{}", w);
			// panic(w);
			return {};
		}
		catch (const std::exception &e)
		{
			std::string w{strip(e.what(), "\n")};
			trace("Exception:\n{:>10}{}", "", w);
			panic(w);
			return {};
		}
	}

	std::vector<std::string> read_csv(std::string_view filename, std::string_view delims = ",\n")
	{
		auto f = read_file(filename.data());
		return split(f, delims);
	}

	std::vector<std::string> read_lines_exact(std::string_view filename, std::string_view delims, include_emptys ie = include_emptys::yes)
	{
		auto s             = read_file(filename);
		bool include_empty = ie == include_emptys::yes;

		auto sl = split_exact(s, delims, include_empty);
		return sl;
	}

	std::vector<std::string> read_lines_delimiter(std::string_view filename, std::string_view delim, include_emptys ie = include_emptys::no)
	{
		auto s = read_file(filename);

		std::vector<std::string> ret;

		if (ie == include_emptys::no)
			ret = split(s, delim);
		else
			ret = read_lines_exact(filename, delim, ie);

		return ret;
	}

	std::vector<std::string> read_lines(std::string_view filename, std::string_view delims = "\n", include_emptys ie = include_emptys::no)
	{
		return read_lines_delimiter(filename, delims, ie);
	}
	std::vector<std::string> read_all_lines(std::string_view filename, std::string_view delims = "\n")
	{
		return read_lines_delimiter(filename, delims, include_emptys::yes);
	}

	template<typename T>
	std::vector<T> read_lines_as(std::string_view filename, std::string_view delims = "\n", include_emptys ie = include_emptys::no)
	{
		if constexpr (std::is_convertible_v<T, std::string>)
			return read_lines_delimiter(filename, delims, ie);
		else if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
			return read_lines_integers_delimiter(filename, delims);
		else
		{
			static_assert(true, "Not implemented");
		}
	}

	template<typename T>
	std::vector<std::optional<T>> read_all_lines_as(std::string_view filename, std::string_view delims = "\n")
	{
		auto lines = read_all_lines(filename, delims);

		if constexpr (std::is_integral_v<T> || std::is_floating_point_v<T>)
		{
			std::vector<std::optional<T>> ret;
			ret.reserve(lines.size());

			for (const auto &v : lines)
			{
				if (v.empty())
					ret.emplace_back(std::nullopt);
				else
					ret.emplace_back(std::optional(to_number<T>(v)));
			}

			return ret;
		}
		else
		{

			static_assert(true, "Not implemented");
		}

		return {};
	}

	template<typename T = i64>
	std::vector<T> read_lines_integers(std::string_view filename)
	{
		auto v = read_lines(filename);

		std::vector<T> ret;
		ret.reserve(v.size());

		for (const auto &i : v)
			ret.push_back(to_number<T>(trim(i).data()));

		return ret;
	}

	std::vector<i64> read_lines_integers_delimiter(std::string_view filename, std::string_view delim = ",\n")
	{
		auto v = read_lines_delimiter(filename, delim);

		std::vector<i64> ret;
		ret.reserve(v.size());

		for (const auto &i : v)
			ret.push_back(to_number<i64>(trim(i).data()));

		return ret;
	}
}
