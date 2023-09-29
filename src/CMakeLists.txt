
#
target_sources(aoc PRIVATE
	Week01/day01.cpp
	#Week01/day02.cpp
	#Week01/day03.cpp
	#Week01/day04.cpp
	#Week01/day05.cpp
	#Week01/day06.cpp
	#Week01/day07.cpp
	#
	#Week02/day08.cpp
	#Week02/day09.cpp
	#Week02/day10.cpp
	#Week02/day11.cpp
	#Week02/day12.cpp
	#Week02/day13.cpp
	#Week02/day14.cpp
	#
	#Week03/day15.cpp
	#Week03/day16.cpp
	#Week03/day17.cpp
	#Week03/day18.cpp
	#Week03/day19.cpp
	#Week03/day20.cpp
	#Week03/day21.cpp
	#
	#Week04/day22.cpp
	#Week04/day23.cpp
	#Week04/day24.cpp
	#Week04/day25.cpp
	main.cpp
)

target_precompile_headers(aoc
  INTERFACE 
  utils/glm/glm.hpp
  utils/standard.hpp
)


target_include_directories(aoc SYSTEM PRIVATE ${CMAKE_CURRENT_LIST_DIR}/utils/glm)


# Modules here
target_sources(aoc 
    PRIVATE 
	FILE_SET cxx_modules TYPE CXX_MODULES FILES
    
    utils/aoc.ixx
    utils/debug.ixx
    utils/math.ixx 
    utils/types.ixx
    utils/print.ixx
    utils/stringhelper.ixx
    utils/readfile.ixx
)



