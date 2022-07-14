project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "Off"

	targetdir("Binaries")
	objdir("!Intermediate")

	files
	{
		"src/glad.c",
		
		"include/glad/glad.h",
		"include/KHR/khrplatform.h"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"