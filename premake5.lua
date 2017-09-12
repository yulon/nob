workspace "nob"
	language "C++"
	flags { "C++11" }
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"x64"}
	objdir("build/obj")
	includedirs { "include" }

	project "nob"
		kind "StaticLib"
		targetdir("lib")
		files {
			"include/*.hpp", "include/*.h",
			"include/nob/shv/*.hpp", "include/nob/shv/*.h",
			"src/*.cpp", "src/*.hpp", "src/*.h"
		}
		targetprefix "lib"
		targetextension ".a"

		configuration "Debug"
			defines { "DEBUG" }
			symbols "On"
			warnings "Extra"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "Speed"

	project "nob_tester"
		kind "SharedLib"
		targetdir("bin")
		files { "test/*.cpp" }
		targetextension ".asi"
		libdirs { "lib" }
		links { "user32", "nob", "psapi", "MinHook" }

		configuration "Debug"
			defines { "DEBUG" }
			symbols "On"
			warnings "Extra"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "Speed"
