@echo off

rem Change the year
set YEAR=2023
set URL="https://adventofcode.com/%YEAR%/day"

rem Session cookie
set SESSION=

if "%SESSION%" == "" (
echo Session key is not set.
exit /b
)



Title AOC %YEAR% Day %1 Input
echo Get AOC %YEAR% Day %1 input...

@if not exist "input" mkdir "input"
curl --silent --cookie "session=%SESSION%" -A "github.com/Masfo/AdventOfCodeTemplate/" %URL%/%1/input -o input\day%1.txt
dir /C /N input\day%1.txt | find "day%1.txt"

@echo. 2> input\day%1test.txt
explorer input\day%1test.txt

rem explorer input\day%1.txt


