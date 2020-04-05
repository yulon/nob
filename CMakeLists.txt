cmake_minimum_required(VERSION 3.13)

project("nob")

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/DepPull.cmake")

DepPull(
	minhook_cpp
	GIT_REPO "https://github.com/yulon/minhook_cpp.git"
	GIT_TAG "f3239f712c42cb949b3be49bba841eb0931c783f"
)

DepPull(
	rua
	GIT_REPO "https://github.com/yulon/rua.git"
	GIT_TAG "e7e1fc6912e2ad2b956cb3c43a2ff497dcb5c706"
)

file(GLOB_RECURSE nob_SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" )
add_library(nob STATIC ${nob_SRC})
set(nob_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(nob PUBLIC ${nob_INCLUDE_DIR})
target_link_libraries(nob PUBLIC minhook_cpp rua version)
set_target_properties(nob PROPERTIES CXX_STANDARD 17)
if(MSVC)
	target_compile_definitions(nob PUBLIC "_CRT_SECURE_NO_WARNINGS")
	target_compile_options(nob PUBLIC "/utf-8")
endif()
if(DEFINED NOB_FAST_LAUNCH AND NOB_FAST_LAUNCH)
	message(STATUS "Nob: Enable 'NOB_FAST_LAUNCH'")
	target_compile_definitions(nob PUBLIC "NOB_FAST_LAUNCH")
endif()

add_library(nob_tester SHARED "${CMAKE_CURRENT_SOURCE_DIR}/tools/tester/main.cpp")
target_include_directories(nob_tester PRIVATE ${nob_INCLUDE_DIRS})
set_target_properties(nob_tester PROPERTIES CXX_STANDARD 17)
set_target_properties(nob_tester PROPERTIES PREFIX "")
set_target_properties(nob_tester PROPERTIES SUFFIX ".asi")
target_link_libraries(nob_tester PRIVATE nob)
if(MSVC)
	target_link_options(nob_tester PRIVATE "/include:DllMain")
else()
	target_link_options(nob_tester PRIVATE "-Wl,--exclude-all-symbols")
endif()
