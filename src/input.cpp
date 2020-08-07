#include "input.h"
#include <curses.h>

static int ch = ERR;

bool key_pressed() {
  ch = wgetch(stdscr);
  return ch != ERR;
}

int get_key() {
  int c = ch;
  ch = ERR;
  return c;
}

Input::Input() {}

Input::~Input() {}

int Input::wait_for_key() {
  while (!key_pressed()) {}
  return get_key();
}