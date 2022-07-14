workspace "RayCast"
   architecture "x64"
   configurations {
       "Debug", 
       "Release",
       "Production"
    }

outputdir = "%{cfg.build}-%{cfg.system}-%{cfg.architecture}"


project "Runtime"
   location "Runtime"
   kind "SharedLib"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/{prj.name}")
   files { "**.h", "**.cpp" }

   includedirs {
       "%{prj.name}/ThirdParty/spdlog/include",
       "%{prj.name}/ThirdParty/assimp/include",
       "%{prj.name}/ThirdParty/Bullet/src",
       "%{prj.name}/ThirdParty/GLEW/include",
       "%{prj.name}/ThirdParty/GLFW/include",
       "%{prj.name}/ThirdParty/GLM/glm",
       "%{prj.name}/ThirdParty/yaml-cpp/include"


   }

   filter "system:windows"
      staticruntime "On"
      systemversion "latest"

      defines {
         "_WINDLL",
         "GLEW_STATIC"
      }

   
   postbuildcommands {
      ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Game/")
   }

   filter "configurations:Debug"
      defines "RAYCAST_DEBUG"
      symbols "On"
   
   filter "configurations:Release"
      defines "RAYCAST_RELEASE"
      optimize "On"

   filter "configurations:Production"
      defines "RAYCAST_PRODUCTION"
      optimize "On"

      
project "Game"
   location "Game"
   kind "ConsoleApp"
   language "C++"
   targetdir ("bin/" .. outputdir .. "/%{prj.name}")
   objdir ("bin-int/" .. outputdir .. "/{prj.name}")
   files { "**.h", "**.cpp" }

   includedirs {
      "%{prj.name}/ThirdParty/spdlog/include",
      "%{prj.name}/ThirdParty/assimp/include",
      "%{prj.name}/ThirdParty/Bullet/src",
      "%{prj.name}/ThirdParty/GLEW/include",
      "%{prj.name}/ThirdParty/GLFW/include",
      "%{prj.name}/ThirdParty/GLM/glm",
      "%{prj.name}/ThirdParty/yaml-cpp/include",
      "Runtime/"  
  }

  links {
     "Runtime"
  }

  filter "system:windows"
     staticruntime "On"
     systemversion "latest"

     defines {
        "GLEW_STATIC"
     }

  filter "configurations:Debug"
     defines "RAYCAST_DEBUG"
     symbols "On"
  
  filter "configurations:Release"
     defines "RAYCAST_RELEASE"
     optimize "On"

  filter "configurations:Production"
     defines "RAYCAST_PRODUCTION"
     optimize "On"
  
