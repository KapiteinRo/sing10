@echo off

if %1.==test. goto libion_test

echo *** CLEANING ***

if exist ions.obj del ions.obj
if exist ion_compiler.obj del ion_compiler.obj
if exist ion_math.obj del ion_math.obj
rem if exist ..\lib_ions.lib del ..\lib_ions.lib
if exist testmath.exe del testmath.exe
if exist testmath.obj del testmath.obj

if %1.==clean. goto libion_end
echo *** BUILDING LIB_IONS ***
rem *** we do want to keep the library during cleaning ***
if exist ..\lib_ions.lib del ..\lib_ions.lib

cl /c /I..\..\include ions.c ion_compiler.c ion_math.c

if not exist ions.obj goto libion_error
if not exist ion_compiler.obj goto libion_error
if not exist ion_math.obj goto libion_error

lib /OUT:..\lib_ions.lib ions.obj ion_compiler.obj ion_math.obj

goto libion_end

:libion_test
echo *** BUILDING TESTS ***
cl /I..\..\include testmath.c ion_math.c
if not exist testmath.exe goto libion_error

goto libion_end

:libion_error
echo *** ERRORS ***

:libion_end
