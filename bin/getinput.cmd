@echo off

rem Change the year
set YEAR=%1
set DAY=%2


rem Session cookie
set SESSION=

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
curl --silent --cookie "session=%SESSION%" -A "github.com/Masfo/AdventOfCodeTemplate/" %URL%/input -o input\day%day%.txt
dir /C /N input\day%DAY%.txt | find "day%DAY%.txt"

@echo. 2> input\day%1test.txt
rem explorer input\day%1test.txt

rem explorer input\day%1.txt

