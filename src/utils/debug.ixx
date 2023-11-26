module;
#include <Windows.h>

export module aoc.debug;
import std;

namespace fs = std::filesystem;

template<typename... Args>
inline void write_to_console(const std::string &str) noexcept
{
	std::print("{}", str);
}

void output_message(const std::string_view message) noexcept
{
#ifdef _DEBUG
	OutputDebugStringA(message.data());
#endif
	std::print("{}", message);
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
	void dbg(const std::format_string<Args...> fmt, Args &&...args)
	{
		output_message(std::vformat(fmt.get(), std::make_format_args(args...)));
	}

	// debugln
	template<typename... Args>
	void dbgln(const std::format_string<Args...> fmt, Args &&...args)
	{
		output_message(std::vformat(fmt.get(), std::make_format_args(args...)));
		output_message("\n");
	}

	void dbgln() { output_message("\n"); }

	template<typename... Args>
	void dbgln_if(bool cond, const std::format_string<Args...> fmt, Args &&...args) noexcept
	{
		if (cond)
		{
			output_message(std::vformat(fmt.get(), std::make_format_args(args...)));
			output_message("\n");
		}
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
	void dbg(const std::format_string<Args...>, Args &&...)
	{
	}

	// debugln
	template<typename... Args>
	void dbgln(const std::format_string<Args...>, Args &&...)
	{
	}

	void dbgln() { }

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
	void println(const std::format_string<Args...> fmt, Args &&...args)
	{
		output_message(std::vformat(fmt.get(), std::make_format_args(args...)));
		output_message("\n");
	}

	void println() noexcept { output_message("\n"); }
} // namespace aoc
