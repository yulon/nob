workspace "nob"
	language "C++"
	flags { "C++11" }
	location ( "build" )
	configurations { "Release" }
	platforms {"x64"}
	objdir("build/obj")
	includedirs { "include" }

	project "nob"
		kind "StaticLib"
		targetdir("lib")
		files {
			"include/*.hpp", "include/*.h",
			"include/nob/shv/*.hpp", "include/nob/shv/*.h",
			"src/*.cpp", "src/*.hpp", "src/*.h",
			"src/shv/*.cpp", "src/shv/*.hpp", "src/shv/*.h",
		}
		targetprefix "lib"
		targetextension ".a"
		defines { "NDEBUG" }
		optimize "Speed"

	project "nob_tester"
		kind "SharedLib"
		targetdir("bin")
		files { "test/*.cpp" }
		targetextension ".asi"
		libdirs { "lib" }
		defines { "NDEBUG" }
		optimize "Speed"
		links { "user32", "nob" }
