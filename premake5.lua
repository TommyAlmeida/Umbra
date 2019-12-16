workspace "Umbra"
	architecture "x86_64"
	startproject "Sandbox"
	configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

flags { "MultiProcessorCompile" }

IncludeDir = {}
IncludeDir["GLFW"] = "Umbra/vendor/GLFW/include"

group "Dependencies"
	include "Umbra/vendor/GLFW"

group ""

project "Umbra"
	location "Umbra"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { 
		"%{prj.name}/src/**.h", 
		"%{prj.name}/src/**.cpp" 
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	pchheader "ubpch.h"
	pchsource "Umbra/src/ubpch.cpp"

	includedirs { 
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
	}

	links {
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines { "UB_PLATFORM_WINDOWS", "UB_BUILD_DLL", "GLFW_INCLUDE_NONE" }

	postbuildcommands { ("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox") }
	
	filter "configurations:Debug"
		defines "UB_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "UB_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "UB_DIST"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files{ "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "Umbra/vendor/spdlog/include", "Umbra/src" }
	
	links { "Umbra" }

	 filter "system:windows"
		 cppdialect "C++17"
		 staticruntime "On"
		 systemversion "latest"

	defines { "UB_PLATFORM_WINDOWS" }

	 filter "configurations:Debug"
		 defines "UB_DEBUG"
		 symbols "On"

	 filter "configurations:Release"
		 defines "UB_RELEASE"
		 optimize "On"

	 filter "configurations:Dist"
		 defines "UB_DIST"
		 optimize "On"