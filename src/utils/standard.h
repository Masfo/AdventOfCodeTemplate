#pragma once


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
				return static_cast<size_t>(result);                                                                                        \
			}                                                                                                                              \
		};                                                                                                                                 \
	}
