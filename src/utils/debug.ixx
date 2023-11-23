module;
#include <Windows.h>

export module aoc.debug;
import std;

namespace fs = std::filesystem;

void output_message(const std::string_view message) noexcept
{
	OutputDebugStringA(message.data());
	std::print("{}", message);
}

template<typename... Args>
inline auto print_util(const std::string &str) noexcept
{

	HANDLE const output_handle = GetStdHandle(STD_OUTPUT_HANDLE);

	const DWORD char_count = static_cast<DWORD>(str.length());
	WriteConsoleA(output_handle, str.data(), char_count, nullptr, nullptr);

	return str;
}

struct alignas(64) FormatLocation
{
	std::string_view     fmt;
	std::source_location loc;

	FormatLocation(const char *s, const std::source_location &l = std::source_location::current()) noexcept
		: fmt(s)
		, loc(l)
	{
	}

	FormatLocation(std::string_view s, const std::source_location &l = std::source_location::current()) noexcept
		: fmt(s)
		, loc(l)
	{
	}
};

export
{

	using namespace std::string_view_literals;
#ifdef _DEBUG
	// debug
	template<typename... Args>
	void dbg(std::string_view fmt, Args && ...args) noexcept
	{
		auto out = std::vformat(fmt, std::make_format_args(args...));
		output_message(out);
	}

	void dbg([[maybe_unused]] std::string_view fmt) noexcept { output_message(std::format("{}"sv, fmt)); }

	// debugln
	template<typename... Args>
	void dbgln(std::string_view fmt, Args && ...args) noexcept
	{
		auto out = std::vformat(fmt, std::make_format_args(args...));
		out.append("\n");
		output_message(out);
	}

	void dbgln(std::string_view fmt) noexcept { output_message(std::format("{}\n"sv, fmt)); }

	void dbgln() noexcept { output_message("\n"); }

	template<typename... Args>
	void dbgln_if(bool cond, std::string_view fmt, Args &&...args) noexcept
	{
		if (cond)
			dbgln(fmt, args...);
	}

	// trace
	template<typename... Args>
	void trace(FormatLocation fmt, [[maybe_unused]] Args && ...args) noexcept
	{
		fs::path    filename = fmt.loc.file_name();
		std::string file     = filename.string();

		if constexpr (sizeof...(args) > 0)
		{
			output_message(std::format("{}({}): {}\n"sv, file, fmt.loc.line(), std::vformat(fmt.fmt, std::make_format_args(args...))));
		}
		else
		{

			output_message(std::format("{}({}): {}\n"sv, file, fmt.loc.line(), fmt.fmt));
		}
	}

	void trace(const std::source_location &loc = std::source_location::current()) noexcept
	{
		//
		output_message(std::format("{}({}):\n", loc.file_name(), loc.line()));
	}

	// Panic
	template<typename... Args>
	[[noreturn]] void panic(std::string_view fmt, Args && ...args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			trace("PANIC: {}", std::vformat(fmt, std::make_format_args(args...)));
		}
		else
		{
			trace("PANIC: {}", fmt);
		}
		if (IsDebuggerPresent())
		{
			DebugBreak();
		}
		FatalExit(0);
		std::unreachable();
	}

	[[noreturn]] void panic() noexcept { panic(""); }

	// assert

	void assert_msg(bool expr, std::string_view message, const std::source_location &loc = std::source_location::current()) noexcept
	{
		if (!expr)
		{
			dbgln("\n***** Assert *****\n\n{}({}): {}\n\n***** Assert *****\n", loc.file_name(), loc.line(), message);

			auto traces = std::stacktrace::current();

			for (const auto &traceline : traces)
			{
				if (traceline.source_file().contains(__FILE__))
					continue;

				dbgln("{}({}): {}", traceline.source_file(), traceline.source_line(), traceline.description());
			}

			dbgln("\n***** Assert *****\n");

			panic();
		}
	}

	void assert(bool expr = false, const std::source_location &loc = std::source_location::current()) noexcept
	{
		assert_msg(expr, "assert", loc);
	}

#else

	template<typename... Args>
	void dbg(std::string_view, Args && ...) noexcept
	{
	}

	void dbg(std::string_view) noexcept { }

	template<typename... Args>
	void dbgln(std::string_view, Args && ...) noexcept
	{
	}

	void dbgln(std::string_view) noexcept { }
	void dbgln() noexcept { }

	template<typename... Args>
	void dbgln_if(bool, std::string_view, Args &&...) noexcept
	{
	}

	template<typename... Args>
	void trace(FormatLocation, Args && ...) noexcept
	{
	}

	void trace() noexcept { }

	template<typename... Args>
	void panic(std::string_view, Args && ...) noexcept
	{
	}

	void panic() noexcept { }

	void assert_msg(bool, std::string_view) noexcept { }

	void assert(bool) noexcept { }

#endif
}

export namespace aoc
{
	// print, println

	// prinlnt("{}Hello {}World {}", red("Hello"), green("World"));

	template<typename... Args>
	void println(std::string_view fmts, Args... args) noexcept
	{
		auto out            = std::vformat(fmts, std::make_format_args(args...));
		out[out.size() - 1] = '\n';

		auto str = print_util(out);
		OutputDebugStringA(out.data());
	}

	void println(std::string_view fmt) noexcept
	{
		auto tmp = std::format("{}\n", fmt);
		auto str = print_util(tmp);
		OutputDebugStringA(tmp.data());
	}

	void println() noexcept
	{
		print_util("\n");
		OutputDebugStringA("\n");
	}
} // namespace aoc
