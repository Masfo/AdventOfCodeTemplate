@echo off

rem Change the year
set YEAR=%1
set DAY=%2


rem Session cookie
set SESSION=53616c7465645f5f21a1a45bb671fcb25d229f032d0d5cf3dbf5d3ad662b526986d33138fbca3524011167b010da9a10692f2e81bcb8395eb584eef391f74bab

if "%SESSION%" == "" (
echo Session key is not set.
exit /b
)

if [%YEAR%] == [] (
echo YEar not set. example: getinput 2023 1
exit /b
)

if [%DAY%] == [] (
echo Day not set. example: getinput 2023 1
exit /b
)

set URL="https://adventofcode.com/%YEAR%/day/%DAY%"

Title AOC %YEAR% Day %DAY% Input
echo Get AOC %YEAR% Day %DAY% input...

@if not exist "input" mkdir "input"
curl --silent --cookie "session=%SESSION%" -A "github.com/Masfo/AdventOfCodeTemplate/" %URL%/input -o input\day%DAY%.txt
dir /C /N input\day%DAY%.txt | find "day%DAY%.txt"

@echo. 2> input\day%DAY%test.txt
rem explorer input\day%1test.txt

rem explorer input\day%1.txt


