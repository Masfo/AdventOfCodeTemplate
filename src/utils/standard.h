#pragma once
#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <filesystem>
#include <format>
#include <fstream>
#include <functional>
#include <limits>
#include <numeric>
#include <optional>
#include <print>
#include <ranges>
#include <set>
#include <source_location>
#include <span>
#include <string>
#include <string_view>
#include <system_error>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace fs = std::filesystem;


#define STD_HASH(T, ...)                                                                                                                   \
	namespace std                                                                                                                          \
	{                                                                                                                                      \
		template<>                                                                                                                         \
		struct hash<T>                                                                                                                     \
		{                                                                                                                                  \
			size_t operator()(const T &value) const                                                                                        \
			{                                                                                                                              \
				i64 result = 0;                                                                                                            \
				hash_combine(result, __VA_ARGS__);                                                                                         \
				return result;                                                                                                             \
			}                                                                                                                              \
		};                                                                                                                                 \
	}
