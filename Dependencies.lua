-- All dependencies used by the engine

IncludeDir = {}
IncludeDir["Assimp"] = "%{wks.location}/ThirdParty/ASSIMP/include"
IncludeDir["Bullet"] = "%{wks.location}/ThirdParty/Bullet/src"
IncludeDir["Glad"] = "%{wks.location}/ThirdParty/Glad/include"
IncludeDir["GLFW"] = "%{wks.location}/ThirdParty/GLFW/include"
IncludeDir["glm"] = "%{wks.location}/ThirdParty/GLM/glm"
IncludeDir["ImGui"] = "%{wks.location}/RayCast/Vendor/imgui"
IncludeDir["ReactPhysics"] = "%{wks.location}/ThirdParty/reactphysics/include"
IncludeDir["spdlog"] = "%{wks.location}/ThirdParty/spdlog-1.x/include"
IncludeDir["yaml_cpp"] = "%{wks.location}/ThirdParty/yaml-cpp/include"

---------------
-- Libraries --
---------------

LibraryDir = {}
LibraryDir["Assimp"] = "%{wks.location}/ThirdParty/ASSIMP/lib"
LibraryDir["Bullet"] = "%{wks.location}/ThirdParty/Bullet/lib"
LibraryDir["GLFW"] = "%{wks.location}/ThirdParty/GLFW/lib-vc2022"
LibraryDir["ReactPhysics"] = "%{wks.location}/ThirdParty/reactphysics/lib"

Library = {}
Library["Assimp"] = "%{LibraryDir.Assimp}/assimpd.lib"
Library["GLFW"] = "%{LibraryDir.GLFW}/glfw3.lib"
Library["ReactPhysics"] = "%{LibraryDir.ReactPhysics}/reactphysics3d.lib"

-- Bullet
Library["BulletCollision"] = "%{LibraryDir.Bullet}/BulletCollision_Debug.lib"
Library["BulletDynamics"] = "%{LibraryDir.Bullet}/BulletDynamics_Debug.lib"
Library["BulletFileLoader"] = "%{LibraryDir.Bullet}/BulletFileLoader_Debug.lib"
Library["BulletMultiThreaded"] = "%{LibraryDir.Bullet}/BulletMultiThreaded_Debug.lib"
Library["BulletSoftBody"] = "%{LibraryDir.Bullet}/BulletSoftBody_Debug.lib"
Library["BulletWorldImporter"] = "%{LibraryDir.Bullet}/BulletWorldImporter_Debug.lib"
Library["BulletXmlWorldImporter"] = "%{LibraryDir.Bullet}/BulletXmlWorldImporter_Debug.lib"
Library["ConvexDecomposition"] = "%{LibraryDir.Bullet}/ConvexDecomposition_Debug.lib"
Library["GImpactUtils"] = "%{LibraryDir.Bullet}/GIMPACTUtils_Debug.lib"
Library["GLUI"] = "%{LibraryDir.Bullet}/GLUI_Debug.lib"
Library["HACD"] = "%{LibraryDir.Bullet}/HACD_Debug.lib"
Library["LinearMath"] = "%{LibraryDir.Bullet}/LinearMath_Debug.lib"
Library["MiniCL"] = "%{LibraryDir.Bullet}/MiniCL_Debug.lib"
Library["OpenGLSupport"] = "%{LibraryDir.Bullet}/OpenGLSupport_Debug.lib"
