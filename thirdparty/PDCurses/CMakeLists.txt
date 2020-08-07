cmake_minimum_required(VERSION 3.2)

project(pdcurses)

option(PDCURSES_WINCON "Set to ON to build for Windows console" ON)
option(PDCURSES_BUILD_DEMOS "Set to ON to build demos" OFF)

add_definitions(-D_CRT_SECURE_NO_WARNINGS)
add_compile_options(
    /wd4267 # disable conversion warning from size_t to long
    /wd4244 # disable conversion warning from long to short
    /wd4996 # disable 'GetVersion' deprecation warning
)

add_subdirectory(pdcurses)
if(PDCURSES_WINCON)
    add_subdirectory(wincon)
    set(PDCURSES_PLATFORM_LIBRARY pdcurses_wincon)
else()
    message(WARNING "You haven't selected a specific platform option, defaulting to Windows console.")
    add_subdirectory(wincon)
    set(PDCURSES_PLATFORM_LIBRARY pdcurses_wincon)
endif()

file(WRITE ${CMAKE_CURRENT_BINARY_DIR}/dummy.c "")

add_library(pdcurses ${CMAKE_CURRENT_BINARY_DIR}/dummy.c)
target_include_directories(pdcurses PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(pdcurses PUBLIC
    pdcurses_base
    ${PDCURSES_PLATFORM_LIBRARY}
)

if(PDCURSES_BUILD_DEMOS)
    message("-- PDCurses: Building demos set")
    add_subdirectory(demos)
endif()