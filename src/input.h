#pragma once

class Input
{
public:
  Input();
  ~Input();

  int wait_for_key();
  int get_key();
};