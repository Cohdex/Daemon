workspace "Daemon"
	architecture "x64"
	configurations { "Debug", "Release", "Dist" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Daemon"
	location "Daemon"
	kind "SharedLib"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files { "%{prj.name}/src/**" }

	includedirs { }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	defines "DMN_EXPORTS"

	filter "configurations:Debug"
		defines "DMN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DMN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DMN_DIST"
		optimize "On"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files "%{prj.name}/src/**"

	includedirs "Daemon/src"

	links "Daemon"

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DMN_DEBUG"
		symbols "On"

	filter "configurations:Release"
		defines "DMN_RELEASE"
		optimize "On"

	filter "configurations:Dist"
		defines "DMN_DIST"
		optimize "On"

	postbuildcommands {
		"{COPY} %{cfg.buildtarget.directory}/../Daemon %{cfg.buildtarget.directory}"
	}