project "RayCast"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++17"
    staticruntime "Off"

    targetdir(BuildDir)
    objdir(IntermediateDir)

    files
    {
        "Source/**.cpp",
        "Source/**.h",

        "stdafx.cpp",
        "stdafx.h"
    }

    includedirs
    {
        "%{wks.location}/RayCast",
        "%{wks.location}/RayCast/resources",

        "Source",

        "%{IncludeDir.Assimp}",
        "%{IncludeDir.Bullet}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.ImGui}",
        "%{IncludeDir.ReactPhysics}",
        "%{IncludeDir.spdlog}",
        "%{IncludeDir.yaml_cpp}"
    }

    libdirs
    {
        "%{LibraryDir.Assimp}",
        "%{LibraryDir.Bullet}",
        "%{LibraryDir.GLFW}",
        "%{LibraryDir.ReactPhysics}"
    }

    links
    {
        "%{Library.Assimp}",
        "%{Library.GLFW}",
        "%{Library.ReactPhysics}",

        "%{Library.BulletCollision}",
        "%{Library.BulletDynamics}",
        "%{Library.BulletFileLoader}",
        "%{Library.BulletMultiThreaded}",
        "%{Library.BulletSoftBody}",
        "%{Library.BulletWorldImporter}",
        "%{Library.BulletXmlWorldImporter}",
        "%{Library.ConvexDecomposition}",
        "%{Library.GImpactUtils}",
        "%{Library.GLUI}",
        "%{Library.HACD}",
        "%{Library.LinearMath}",
        "%{Library.MiniCL}",
        "%{Library.OpenGLSupport}",

        "ImGui",
        "Glad",
        "yaml-cpp",
        "opengl32.lib"
    }

    filter "system:windows"
        systemversion "latest"

    filter "configurations:Debug"
        runtime "Debug"
        symbols "On"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "configurations:Distribution"
        runtime "Release"
        optimize "On"