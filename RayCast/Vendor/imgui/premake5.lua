project "ImGui"
    kind "StaticLib"
    language "C++"
    staticruntime "Off"

    targetdir("Binaries")
    objdir("!Intermediate")

    files
    {
        "*.cpp",
        "*.h"
    }

    includedirs
    {
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}"
    }

  filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		runtime "Release"
		optimize "on"

    filter "configurations:Dist"
		runtime "Release"
		optimize "on"
        symbols "off"
