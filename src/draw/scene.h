#include <iostream>
#include <stdio.h>
#include <iterator>
#include <GL/glut.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include "../logic/playgrnd.h"

#define MAXOBJS 100
class hbz{
    playground* doska;
    int old_x, old_y, moving;

    void stone(float size);
public:
    float spin_x;
    float spin_y;
    double epoch;
    GLint windW, windH;
    GLint viewport[4];
    GLuint selectBuf[MAXOBJS];
    uint n,m;
    void Init();
    void Draw(void);
    void disppole();
    void FixPos(GLint h);
    //void ai();

    hbz();
    ~hbz();

};
