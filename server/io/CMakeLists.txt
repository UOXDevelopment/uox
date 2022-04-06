cmake_minimum_required(VERSION 3.12.3)

project(ultima VERSION 0.01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if (WIN32)
set(CMAKE_CXX_FLAGS_RELEASE "/O2")
elseif (APPLE)
set(CMAKE_CXX_FLAGS_RELEASE "-Os")
else ()
set(CMAKE_CXX_FLAGS_RELEASE "-O2")
endif()

add_library(io 
	STATIC
		console.cpp
		logger.cpp
)


target_include_directories(io 
	PRIVATE
		../utility
		../clientobjects
		../system
		../types
		../ultima
if(WIN32)
		../../support/zlib/win64
endif()
)

		
target_compile_options(io 
	PRIVATE
		$<$<PLATFORM_ID:Windows>:/W3>

		$<$<PLATFORM_ID:Linux>:-Wno-unused-result>
)

target_compile_definitions(io
	PRIVATE
		$<$<PLATFORM_ID:Windows>:_LIB>
		$<$<PLATFORM_ID:Windows>:_UNICODE>
		$<$<PLATFORM_ID:Windows>:UNICODE>
		NDEBUG
)



