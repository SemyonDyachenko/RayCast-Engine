@echo off

echo Generating Visual Studio project files

call ThirdParty\Premake\premake5.exe vs2022
PAUSE