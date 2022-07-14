include "Dependencies.lua"

workspace "RayCast"
    architecture "x86_64"
    startproject "RayCast"

    configurations
    {
        "Debug",
        "Release",
        "Distribution"
    }

BuildDir = "%{wks.location}/Binaries/%{prj.name}"
IntermediateDir = "%{wks.location}/Intermediate/%{prj.name}"

group "Dependencies"
    include "ThirdParty/Glad"
    include "ThirdParty/yaml-cpp"
    include "RayCast/Vendor/imgui"
group ""

include "RayCast"