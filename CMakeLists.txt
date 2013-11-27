cmake_minimum_required (VERSION 2.6)
project (taveren)

set (CXX $ENV{CXX})
if (CXX)
  set (CMAKE_CXX_COMPILER ${CXX})
endif ()

add_library (taveren taveren.cpp)

add_executable (test_tavn test.cpp)

add_definitions (-std=c++0x -Wall -Werror -g
  -D_GNU_SOURCE -D_GLIBCXX_USE_NANOSLEEP)
if (CMAKE_BUILD_TYPE STREQUAL RelWithDebInfo)
  add_definitions (-DNDEBUG)
endif ()

set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_MODULE_PATH})
include (FindLua52.cmake)

# for tests, lib doesn't need to link to other libs
find_library (luapp luapp)
target_link_libraries (test_tavn taveren luapp)
find_package (Lua52)
message ("lua5.2 libs: ${LUA_LIBRARIES}")
include_directories (${LUA_INCLUDE_DIR})
target_link_libraries (test_tavn ${LUA_LIBRARIES})

# install (DIRECTORY bin install etc DESTINATION . USE_SOURCE_PERMISSIONS
#   PATTERN .svn EXCLUDE)
install (TARGETS taveren ARCHIVE DESTINATION lib)
install (FILES taveren.hpp DESTINATION include)
