workspace "Daemon"
	architecture "x86_64"
	configurations { "Debug", "Develop", "Release" }
	startproject "Test"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Daemon"
	location "Daemon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "Daemon/src/pch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src/",
		"%{prj.name}/extlib/GLM/include/"
	}

	links {
		"glad",
		"OpenGL32"
	}

	defines {
		"DMN_EXPORTS"
	}

	filter "system:windows"
		systemversion "latest"

		includedirs {
			"%{prj.name}/extlib/GLFW/include/"
		}
		libdirs {
			"%{prj.name}/extlib/GLFW/"
		}
		links {
			"glfw3"
		}

	filter { "configurations:Debug or Develop" }
		includedirs {
			"%{prj.name}/extlib/Glad/Glad-debug/include/"
		}
		libdirs {
			"%{prj.name}/extlib/Glad/Glad-debug/"
		}

	filter { "configurations:Release" }
		includedirs {
			"%{prj.name}/extlib/Glad/Glad/include/"
		}
		libdirs {
			"%{prj.name}/extlib/Glad/Glad/"
		}

	filter "configurations:Debug"
		defines "DMN_DEBUG"
		symbols "On"
		optimize "Off"
		runtime "Debug"
		
	filter "configurations:Develop"
		defines "DMN_DEVELOP"
		symbols "Off"
		optimize "On"
		runtime "Release"

	filter "configurations:Release"
		defines "DMN_RELEASE"
		symbols "Off"
		optimize "Full"
		runtime "Release"

project "Test"
	location "Test"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	files "%{prj.name}/src/**"

	includedirs {
		"Daemon/src"
	}

	links {
		"Daemon"
	}

	filter "system:windows"
		systemversion "latest"

	filter "configurations:Debug"
		defines "DMN_DEBUG"
		symbols "On"
		optimize "Off"
		runtime "Debug"
		
	filter "configurations:Develop"
		defines "DMN_DEVELOP"
		symbols "Off"
		optimize "On"
		runtime "Release"

	filter "configurations:Release"
		defines "DMN_RELEASE"
		symbols "Off"
		optimize "Full"
		runtime "Release"
