@echo off
pushd ..\
call vendor\bin\premake\premake5.exe vs2019
popd
PAUSE
#IF %ERRORLEVEL% NEQ 0 (
#	PAUSE
#)