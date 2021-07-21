workspace "Engine"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

group "Engine"

project "Engine"
	location "engine"
	kind "StaticLib"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")
	
	pchheader "engine_pch.h"
	pchsource "engine/precompiled/engine_pch.cpp"
	
	files
	{
		"%{prj.name}/enginecode/**.h",
		"%{prj.name}/enginecode/**.cpp",
		"engine/precompiled/engine_pch.h",
		"engine/precompiled/engine_pch.cpp"
	}

	includedirs
	{
		"%{prj.name}/enginecode/",
		"%{prj.name}/enginecode/include/independent",
		"%{prj.name}/enginecode/include/",
		"%{prj.name}/precompiled/",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/Glad/include",
		"vendor/glm/",
		"vendor/STBimage",
		"vendor/freetype2/include",
		"vendor/json/single_include/nlohmann",
		"vendor/IMGui",
		"vendor/vendor/enTT/single_include/",
		"vendor/vendor/luaBridge/Source",
		"vendor/vendor/assimp/include",
		"vendor/vendor/box2d/include",
		"vendor/vendor/lua",
		"vendor/vendor/react3D/include",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"


	}
	
	libdirs
	{
		"vendor/FMOD/core/lib/x64",
		"vendor/FMOD/fsbank/lib/x64",
		"vendor/FMOD/studio/lib/x64"
	}

	links 
	{
		"GLFW",
		"Glad",
		"Freetype",
		"IMGui",
		"assimp",
		"box2d",
		"lua",
		"ReactPhysics3d"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

		links
		{
			"fmodL_vc.lib",
			"fmodstudioL_vc.lib"
		}

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

		links
		{
			"fmodL_vc.lib",
			"fmodstudioL_vc.lib"
		}


project "Sandbox"
	location "sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/",
		"engine/precompiled/",
		"vendor/glfw/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/json/single_include/nlohmann",
		"vendor/IMGui",
		"vendor/vendor/enTT/single_include/",
		"vendor/vendor/luaBridge/Source",
		"vendor/vendor/assimp/include",
		"vendor/vendor/box2d/include",
		"vendor/vendor/lua",
		"vendor/freetype2/include",
		"vendor/vendor/react3D/include",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"
	}
	
	links
	{
		"Engine",
	}
	
	debugenvs
	{
						 		"PATH=PATH;../vendor/FMOD/core/lib/x64;../vendor/FMOD/studio/lib/x64"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

 project "EngineTests"
		location "engineTests"
        kind "ConsoleApp"
        language "C++"
		staticruntime "off"
		systemversion "latest"

		targetdir ("bin/" .. outputdir .. "/%{prj.name}")
		objdir ("build/" .. outputdir .. "/%{prj.name}")

        files 
		{ 
			"%{prj.name}/include/*.h",
			"%{prj.name}/src/*.cpp"
		}

        includedirs
		{ 
			"%{prj.name}/include/",
			"vendor/googletest/googletest/include",
			"engine/enginecode/",
			"engine/enginecode/include/independent",
			"engine/enginecode/include/platform",
			"engine/precompiled/",
			"vendor/spdlog/include",
			"vendor/glfw/include",
			"vendor/Glad/include",
			"vendor/glm/",
			"vendor/STBimage",
			"vendor/freetype2/include",
			"vendor/vendor/enTT/single_include/",
			"vendor/vendor/luaBridge/Source",
			"vendor/vendor/assimp/include",
			"vendor/vendor/box2d/include",
			"vendor/vendor/lua",
			"vendor/vendor/react3D/include"
		}

        links 
		{ 
			"googletest"
		}
		
		filter "configurations:Debug"
			runtime "Debug"
			symbols "On"

		filter "configurations:Release"
			runtime "Release"
			optimize "On"

project "Tool"
	location "Tool"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
	}

	includedirs
	{
		"%{prj.name}/include",
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/",
		"engine/precompiled/",
		"vendor/glfw/include",
		"vendor/glm/",
		"vendor/spdlog/include",
		"vendor/json/single_include/nlohmann",
		"vendor/IMGui",
		"vendor/vendor/enTT/single_include/",
		"vendor/vendor/luaBridge/Source",
		"vendor/vendor/assimp/include",
		"vendor/vendor/box2d/include",
		"vendor/vendor/lua",
		"vendor/freetype2/include",
		"vendor/vendor/react3D/include",
		"vendor/FMOD/core/inc",
		"vendor/FMOD/fsbank/inc",
		"vendor/FMOD/studio/inc"

	}

	links
	{
		"Engine",
	}

	debugenvs
	{				 		"PATH=PATH;../vendor/FMOD/core/lib/x64;../vendor/FMOD/studio/lib/x64"
	}


	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "NG_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "NG_RELEASE"
		runtime "Release"
		optimize "On"

project "Spike"
	location "spike"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"engine/enginecode/",
		"engine/enginecode/include/independent",
		"engine/enginecode/include/platform",
		"engine/precompiled/",
		"%{prj.name}/include",
		"vendor/spdlog/include",
		"vendor/STBimage",
		"vendor/freetype2/include",
		"vendor/glm/",
		"vendor/Glad/include",
		"vendor/glfw/include",
		"vendor/json/single_include/nlohmann"
	}
	
	links 
	{
		"Engine",
		"Freetype",
		"Glad",
		"GLFW",
		"IMGui",
		"assimp",
		"box2d",
		"lua",
		"ReactPhysics3d"
	}
	
	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"
		defines
		{
			"NG_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		runtime "Release"
		optimize "On"

group "Vendor"



	include "vendor/glfw"
	include "vendor/googletest"
	include "vendor/Glad"
	include "vendor/freetype2"
	include "vendor/IMGui"
	include "vendor/vendor/assimp"
	include "vendor/vendor/box2d"
	include "vendor/vendor/lua"
	include "vendor/vendor/react3D"