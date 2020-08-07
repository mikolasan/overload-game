cmake_minimum_required(VERSION 3.2)
project(pdcurses_wincon)
add_library(pdcurses_wincon
    pdcclip.c
    pdcdisp.c
    pdcgetsc.c
    pdckbd.c
    pdcscrn.c
    pdcsetsc.c
    pdcutil.c pdcwin.h
)
if (MSVC)
    target_compile_definitions(pdcurses_wincon PRIVATE _CRT_SECURE_NO_WARNINGS=1)
endif()
target_include_directories(pdcurses_wincon PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
