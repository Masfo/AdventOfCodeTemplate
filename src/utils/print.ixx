module;
#include "standard.h"


export module print;
import debug;
import standard;


export
{

	template<typename... Args>
	void print(std::string_view fmts, Args... args) noexcept
	{
#ifdef _DEBUG
		std::string tmp = std::vformat(fmts, std::make_format_args(args...));
		dbg("{}", tmp);
		std::print("{}", tmp);
#endif
	}

	template<typename... Args>
	void println(std::string_view fmts, Args... args) noexcept
	{
		std::string tmp = std::vformat(fmts, std::make_format_args(args...));
		dbgln("{}", tmp);
		std::println("{}", tmp);
	}

	void println() noexcept
	{
		dbgln();
		std::println("");
	}
}
