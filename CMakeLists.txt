cmake_minimum_required(VERSION 3.10)
project(test_app)

set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE(PkgConfig REQUIRED)
PKG_CHECK_MODULES(GTKMM REQUIRED gtkmm-3.0)

INCLUDE_DIRECTORIES(${GTKMM_INCLUDE_DIRS})
LINK_DIRECTORIES(${GTKMM_LIBRARY_DIRS})
ADD_DEFINITIONS(${GTKMM_CFLAGS_OTHER})



add_executable(lua_draw main.cpp gtk_app.cpp gtk_app.h logger.h draw_area.cpp draw_area.h)

target_link_libraries(lua_draw ${GTKMM_LIBRARIES})