module;
#include <Windows.h>

export module aoc.debug;

import std;

void output_message(const std::string_view message) noexcept { OutputDebugStringA(message.data()); }

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

static_assert(64 == sizeof(FormatLocation), "FormatLocation is not 64 bytes");

#if 0
export
{
	using namespace std::string_view_literals;

	// debug
	template<typename... Args>
	void dbg(std::string_view fmt, Args && ...args) noexcept
	{
		output_message(std::format("{}"sv, std::vformat(fmt, std::make_format_args(args...))));
	}

	void dbg(std::string_view fmt) noexcept { output_message(std::format("{}"sv, fmt)); }

	// debugln
	template<typename... Args>
	void dbgln(std::string_view fmt, Args && ...args) noexcept
	{
		output_message(std::format("{}\n"sv, std::vformat(fmt, std::make_format_args(args...))));
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
	void trace(FormatLocation fmt, Args && ...args) noexcept
	{
		output_message(
			std::format("{}({}): {}\n"sv, fmt.loc.file_name(), fmt.loc.line(), std::vformat(fmt.fmt, std::make_format_args(args...))));
	}

	void trace(FormatLocation fmt) noexcept { output_message(std::format("{}({}): {}\n"sv, fmt.loc.file_name(), fmt.loc.line(), fmt.fmt)); }

	void trace() noexcept { output_message("\n"); }

	// Panic
	template<typename... Args>
	[[noreturn]] void panic(std::string_view fmt, Args && ...args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			trace("PANIC: ", std::vformat(fmt, std::make_format_args(args...)));
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
}
#endif
