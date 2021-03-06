#include <iostream>
#include <stdio.h>
#include <iterator>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../logic/playgrnd.h"

class hbz
{
  playground *doska;
  int old_x, old_y, moving;

  void stone(float size);

public:
  float spin_x;
  float spin_y;
  float phi;
  float theta;
  double epoch;
  GLint windW, windH;
  GLint viewport[4];

  uint n, m;
  void Init();
  void Draw(int xPos = 0, int yPos = 0);
  void reshape(int width, int height);
  void render_field();
  void process_hits(GLint h);

  hbz();
  ~hbz();
};
