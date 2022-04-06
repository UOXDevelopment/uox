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

add_library(clientobjects 
	STATIC
		baseobj.cpp
		factory.cpp
		itemobj.cpp
		mobobj.cpp
		playerobj.cpp
		serial_generator.cpp
)


target_include_directories(clientobjects 
	PRIVATE
		../utility
		../io
		../system
		../types
		../ultima
if(WIN32)
		../../support/zlib/win64
endif()
)

		
target_compile_options(clientobjects 
	PRIVATE
		$<$<PLATFORM_ID:Windows>:/W3>

		$<$<PLATFORM_ID:Linux>:-Wno-unused-result>
)

target_compile_definitions(clientobjects
	PRIVATE
		$<$<PLATFORM_ID:Windows>:_LIB>
		$<$<PLATFORM_ID:Windows>:_UNICODE>
		$<$<PLATFORM_ID:Windows>:UNICODE>
		NDEBUG
)



