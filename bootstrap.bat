@echo off
echo ##### Make Visual Studio Projecct #####

cmd.exe /C git clone --recurse-submodules https://github.com/microsoft/vcpkg
cmd.exe /C .\ThirdParty\vcpkg\bootstrap-vcpkg.bat
cmd.exe /C .\ThirdParty\vcpkg\vcpkg install freeglut glew
cmd.exe /C .\ThirdParty\vcpkg\vcpkg integrate install


echo ##### End Visual Studio Project #####

IF "%1" == "EXEC" (
	goto END
) ELSE (
	goto PARAM
)

:PARAM
PAUSE
goto END
