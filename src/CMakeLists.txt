
cmake_minimum_required (VERSION 3.28)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

set_property(TARGET aoc PROPERTY CXX_STANDARD 23)
set_property(TARGET aoc PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET aoc PROPERTY CXX_EXTENSIONS OFF)
#


#add_library(libaoc)


set(CMAKE_DISABLE_SOURCE_CHANGES OFF)
configure_file(	
        $ENV{VCToolsInstallDir}modules/std.ixx
        ${CMAKE_CURRENT_LIST_DIR}/utils/std.ixx
        COPYONLY
)
set(CMAKE_DISABLE_SOURCE_CHANGES ON)

target_sources(aoc PRIVATE
	main.cpp
)

# Modules here
target_sources(aoc 
    PRIVATE 
	FILE_SET cxx_modules TYPE CXX_MODULES FILES

	utils/std.ixx

    utils/aoc.ixx
    utils/types.ixx
    utils/debug.ixx
    utils/math.ixx 
	utils/polygon.ixx
	utils/vec.ixx
	utils/walker.ixx
	utils/tree.ixx
	utils/grid.ixx
	utils/grid2d.ixx
	utils/graph.ixx
	utils/helpers.ixx

	utils/sprite.ixx
	utils/ppm.ixx

    utils/stringhelper.ixx
    utils/stringsplit.ixx

    utils/readfile.ixx

	#
	days.ixx
	#
    Week01/day01.ixx
	Week01/day02.ixx
	Week01/day03.ixx
	Week01/day04.ixx
	Week01/day05.ixx
	Week01/day06.ixx
	Week01/day07.ixx
	#
	Week02/day08.ixx
	Week02/day09.ixx
	Week02/day10.ixx
	Week02/day11.ixx
	Week02/day12.ixx
	Week02/day13.ixx
	Week02/day14.ixx
	#
	Week03/day15.ixx
	Week03/day16.ixx
	Week03/day17.ixx
	Week03/day18.ixx
	Week03/day19.ixx
	Week03/day20.ixx
	Week03/day21.ixx
	#
	Week04/day22.ixx
	Week04/day23.ixx
	Week04/day24.ixx
	Week04/day25.ixx



)




