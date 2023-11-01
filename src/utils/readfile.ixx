module;


export module aoc.readfile;
import std;

import aoc.debug;
import aoc.types;
import aoc.stringhelper;

namespace fs = std::filesystem;

enum class include_emptys
{
	yes,
	no,
};

export
{

	//
	// std::generator<std::string_view> read_lines(
	//	std::filesystem::path & file, std::string_View delims = "\n", include_emptys ie = include_emptys::no)
	//{
	//}


	std::vector<std::string> read_all_lines(const std::filesystem::path &path, include_emptys ie = include_emptys::no)
	{
		auto lines = std::vector<std::string>{};

		if (!fs::exists(path))
			throw fs::filesystem_error(std::format("File not found: {}\n", path.filename().string()),
									   std::make_error_code(std::errc::no_such_file_or_directory));

		auto stream = std::ifstream{path};
		auto line   = std::string{};
		while (std::getline(stream, line))
		{
			if (line.empty() && ie == include_emptys::no)
				continue;

			lines.emplace_back(line);
		}

		return lines;
	}

	inline std::string read_file(std::string_view filename)
	{
		try
		{
			if (!fs::exists(filename))
				throw fs::filesystem_error(std::format("File not found: {}\n", filename),
										   std::make_error_code(std::errc::no_such_file_or_directory));

			std::ifstream ifile(filename.data());
			std::string   str{(std::istreambuf_iterator<char>(ifile)), std::istreambuf_iterator<char>()};

			// str.push_back('\n');
			return str;
		}
		catch (const std::filesystem::filesystem_error &e)
		{
			std::string w{strip(e.what(), "\n")};
			aoc::trace("{}", w);
			return {};
		}
		catch (const std::exception &e)
		{
			std::string w{strip(e.what(), "\n")};
			aoc::trace("Exception:\n{:>10}{}\n", "", w);
			return {};
		}
	}


	std::vector<std::string> read_csv(std::string_view filename, std::string_view delims = ",\n")
	{
		auto f = read_file(filename.data());
		return split(f, delims);
	}


	std::vector<std::string> read_lines_exact(std::string_view filename, std::string_view delims, include_emptys ie = include_emptys::no)
	{
		auto s             = read_file(filename);
		bool include_empty = ie == include_emptys::yes;
		auto sl            = split_exact(s, delims, include_empty);
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

	std::vector<i64> read_lines_integers(std::string_view filename)
	{
		auto v = read_lines(filename);

		std::vector<i64> ret;
		ret.reserve(v.size());

		for (const auto &i : v)
			ret.push_back(to_number<i64>(trim(i).data()));

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
