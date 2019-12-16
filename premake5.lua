workspace "Umbra"
	architecture "x64"
	configurations {"Debug","Release","Dist"}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Umbra"
	location "Umbra"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "ubpch.h"
	pchsource "Umbra/src/ubpch.cpp"

	files { "%{prj.name}/src/**.h", "%{prj.name}/src/**.cpp" }
	includedirs { "%{prj.name}/vendor/spdlog/include" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines { "UB_PLATFORM_WINDOWS", "UB_BUILD_DLL" }

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