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
	OutputDebugStringA(message.data());
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

constexpr std::string_view Black   = "\u001b[30;1m";
constexpr std::string_view Red     = "\u001b[31;1m";
constexpr std::string_view Green   = "\u001b[32;1m";
constexpr std::string_view Yellow  = "\u001b[33;1m";
constexpr std::string_view Blue    = "\u001b[34;1m";
constexpr std::string_view Magenta = "\u001b[35;1m";
constexpr std::string_view Cyan    = "\u001b[36;1m";
constexpr std::string_view White   = "\u001b[37;1m";
constexpr std::string_view Reset   = "\u001b[0m";

export
{

	template<typename T>
	std::string color(std::string_view color, T value)
	{
		return std::format("{}{}{}", color, value, Reset);
	}

	template<typename T>
	std::string red(T value)
	{
		return color(Red, value);
	}

	template<typename T>
	std::string green(T value)
	{
		return color(Green, value);
	}

	template<typename T>
	std::string yellow(T value)
	{
		return color(Yellow, value);
	}

	template<typename T>
	std::string white(T value)
	{
		return color(White, value);
	}

	template<typename T>
	std::string blue(T value)
	{
		return color(Blue, value);
	}

	template<typename T>
	std::string magenta(T value)
	{
		return color(Magenta, value);
	}

	template<typename T>
	std::string cyan(T value)
	{
		return color(Cyan, value);
	}

	template<typename T>
	std::string black(T value)
	{
		return color(Black, value);
	}
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
