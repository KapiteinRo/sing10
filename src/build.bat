@echo off

echo *** CLEANING ***

if exist sing10.dll del sing10.dll
if exist test.exe del test.exe
if exist sing10.lib del sing10.lib
if exist test.obj del test.obj
if exist stack.obj del stack.obj

if %1.==clean. goto buildsrc_end

echo *** BUILDING TEST ***

if %1.==nolib. goto buildsrc_compile

cd ..\lib
call buildall
cd ..\src

:buildsrc_compile
cd ..\lib
if exist sing10.dll copy sing10.dll ..\src\sing10.dll
if exist sing10.lib copy sing10.lib ..\src\sing10.lib
cd ..\src

cl /I..\include test.c stack.c
if exist test.exe upx -9 -q test.exe

cd ..\test
if exist sing10.dll del sing10.dll
if exist test.exe del test.exe
cd ..\src

if exist sing10.dll copy sing10.dll ..\test\sing10.dll
if exist test.exe copy test.exe ..\test\test.exe

:buildsrc_end
