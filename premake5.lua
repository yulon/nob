workspace "nob"
	language "C++"
	cppdialect "C++17"
	location ( "build" )
	configurations { "Debug", "Release" }
	platforms {"x64"}
	objdir("build/obj")
	includedirs { "include", "deps" }

	project "nob"
		kind "StaticLib"
		targetdir("lib")
		files {
			"include/*.hpp", "include/*.h",

			"include/nob/*.hpp", "include/nob/*.h",

			"include/nob/ntv/*.hpp", "include/nob/ntv/*.h",

			"include/nob/shv/*.hpp", "include/nob/shv/*.h",

			"src/*.cpp", "src/*.hpp", "src/*.h",

			"src/ntv/*.cpp", "src/ntv/*.hpp", "src/ntv/*.h",
			"src/ntv/fhtt/*.inc"
		}

		configuration { "gmake" }
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
		links { "user32", "nob", "psapi", "version", "MinHook" }

		configuration { "gmake" }
			linkoptions { "-Wl,--exclude-all-symbols" }

		configuration "Debug"
			defines { "DEBUG" }
			symbols "On"
			warnings "Extra"

		configuration "Release"
			defines { "NDEBUG" }
			optimize "Speed"
