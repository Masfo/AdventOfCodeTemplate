module;
#include <windows.h>
#include "standard.h"


export module debug;

using namespace std::string_view_literals;

struct FormatLocation
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

void print_to_debugln(std::string_view data) noexcept
{
#ifdef _DEBUG
#if defined(_WIN32)
	OutputDebugStringA(data.data());
	OutputDebugStringA("\n");
#endif
#endif
}

void print_to_debug(std::string_view data) noexcept
{
#ifdef _DEBUG
#if defined(_WIN32)
	OutputDebugStringA(data.data());
#endif
#endif
}

void print_to_debugln(std::span<uint8_t> data) noexcept
{
#ifdef _DEBUG
#if defined(_WIN32)
	std::string buffer;
	buffer.reserve(data.size());
	for (const auto &i : data)
		buffer.push_back((char)i);

	buffer.push_back('\n');
	OutputDebugStringA(buffer.c_str());
#endif
#endif
}

export
{
	using namespace std::string_view_literals;


	void dbgln() noexcept { print_to_debug("\n"); }

#ifdef _DEBUG
	template<typename... Args>
	void dbgln(std::string_view fmts, Args... args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			std::string tmp = std::vformat(fmts, std::make_format_args(args...));
			print_to_debugln(tmp);
		}
		else
		{
			print_to_debugln(fmts);
		}
	}

	template<typename... Args>
	void dbgln_if(bool condition, std::string_view fmts, Args... args) noexcept
	{
		if (condition)
			dbgln(fmts, args...);
	}

	void dbgln(std::span<uint8_t> data) noexcept { print_to_debugln(data); }

#else
	template<typename... Args>
	void dbgln(std::string_view, Args && ...) noexcept
	{
	}

	void dbgln(std::span<uint8_t>) noexcept { }

	template<typename... Args>
	void dbgln_if(bool, std::string_view, Args...) noexcept
	{
	}


#endif


#ifdef _DEBUG
	template<typename... Args>
	void dbg(std::string_view fmts, Args && ...args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			std::string tmp = std::vformat(fmts, std::make_format_args(args...));
			print_to_debug(tmp);
		}
		else
		{
			print_to_debug(fmts);
		}
	}

	template<typename... Args>
	void dbg_if(bool condition, std::string_view fmts, Args &&...args) noexcept
	{
		if (condition)
			dbg(fmts, args...);
	}
#else
	template<typename... Args>
	void dbg(std::string_view, Args && ...) noexcept
	{
	}

	template<typename... Args>
	void dbg_if(bool, std::string_view, Args &&...) noexcept
	{
	}
#endif

	// trace
#ifdef _DEBUG
	template<typename... Args>
	void trace(FormatLocation fmt, Args && ...args) noexcept
	{
		if constexpr (sizeof...(Args) > 0)
			dbgln("{}({}): {}", fmt.loc.file_name(), fmt.loc.line(), std::vformat(fmt.fmt, std::make_format_args(args...)));
		else
			dbgln("{}({}): {}", fmt.loc.file_name(), fmt.loc.line(), fmt.fmt);
	}
#else
	template<typename... Args>
	void trace(FormatLocation, Args && ...) noexcept
	{
	}
#endif


	void DebugHalt()
	{
		if (IsDebuggerPresent())
		{
			auto traces = std::stacktrace::current(1);

			for (const auto &trace : traces | std::views::reverse)
				dbgln("{}({}): {}", trace.source_file(), trace.source_line(), trace.description());

			DebugBreak();
		}
	}

} // namespace piku
