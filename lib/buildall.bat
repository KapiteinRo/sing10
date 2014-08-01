@echo off

echo *** CLEANING ***

if exist sing10.res del sing10.res
if exist sing10.obj del sing10.obj
if exist sing10.exp del sing10.exp
if exist sing10.lib del sing10.lib

cd ion
call build clean
cd ..

if %1.==clean. goto sing10_end

echo *** BUILDING LIBRARIES ***

cd ion
call build

cd ..

echo *** BUILDING SING10 ***

rc /dWIN32 /r sing10.rc

cl /c /I..\include sing10.c

if exist sing10.obj link /out:sing10.dll /dll /implib:sing10.lib /def:sing10.def sing10.obj sing10.res

goto sing10_end

:sing10_end
