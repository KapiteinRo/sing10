@echo off

cd ..\src

if %1.==nolib. goto buildtest_nolib

call build
goto buildtest_end

:buildtest_nolib
call build nolib

:buildtest_end
cd ..\test
