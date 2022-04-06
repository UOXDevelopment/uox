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

add_subdirectory(./clientobjects)
add_subdirectory(./io)
add_subdirectory(./system)
add_subdirectory(./types)
add_subdirectory(./ultima)
add_subdirectory(./utility)


add_executable(uox 
		main.cpp
)

if(WIN32)
target_link_libraries(uox PUBLIC
	clientobjects
	io
	system
	types
	ultima
	utility
	-lWs2_32
	-L../support/zlib/win64/lib
	-lzlib

)
else()
target_link_libraries(uox PUBLIC
	clientobjects
	io
	system
	types
	ultima
	utility
	-lz

)
endif()
target_include_directories(uox 
	PRIVATE
		./clientobjects
		./utility
		./io
		./system
		./types
		./ultima
if(WIN32)
		../support/zlib/win64
endif()
)

		
target_compile_options(uox 
	PRIVATE
		$<$<PLATFORM_ID:Windows>:/W3>

		$<$<PLATFORM_ID:Linux>:-Wno-unused-result>
)

target_compile_definitions(uox
	PRIVATE
		$<$<PLATFORM_ID:Windows>:_LIB>
		$<$<PLATFORM_ID:Windows>:_UNICODE>
		$<$<PLATFORM_ID:Windows>:UNICODE>
		NDEBUG
)



