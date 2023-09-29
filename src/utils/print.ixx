module;
#include <format>
#include <print>
#include <string_view>


export module print;

// import debug;

export namespace aoc
{

	template<typename... Args>
	void print(const std::string_view fmts, Args... args) noexcept
	{
#ifdef _DEBUG
		// std::string tmp = std::vformat(fmts, std::make_format_args(args...));
		//  dbg("{}", tmp);
		//  std::print("{}", tmp);
#endif
	}

	template<typename... Args>
	void println(std::string_view fmts, Args&&... args) noexcept
	{
		if constexpr (sizeof...(args) > 0)
		{
			std::string tmp = std::vformat(fmts, std::make_format_args(args...));
			std::println(tmp);
		}
		else
		{
			std::println(fmts);
		}
	}

} // namespace aoc
