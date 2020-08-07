cmake_minimum_required(VERSION 3.2)
project(pdcurses_base)
add_library(pdcurses_base
    addch.c
    addchstr.c
    addstr.c
    attr.c
    beep.c
    bkgd.c
    border.c
    clear.c
    color.c
    debug.c
    delch.c
    deleteln.c
    getch.c
    getstr.c
    getyx.c
    inch.c
    inchstr.c
    initscr.c
    inopts.c
    insch.c
    insstr.c
    instr.c
    kernel.c
    keyname.c
    mouse.c
    move.c
    outopts.c
    overlay.c
    pad.c
    panel.c
    printw.c
    refresh.c
    scanw.c
    scr_dump.c
    scroll.c
    slk.c
    termattr.c
    touch.c
    util.c
    window.c
)
if (MSVC)
    target_compile_definitions(pdcurses_base PRIVATE _CRT_SECURE_NO_WARNINGS=1)
endif()
target_include_directories(pdcurses_base PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
