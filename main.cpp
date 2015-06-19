#include <GL/glut.h>
#include <stdlib.h>

#include "draw/scene.h"


hbz game;
/* GLUT callback Handlers */

static void resize(int width, int height)
{
    /*
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
    */
    game.windW = width;
    game.windH = height;
	glViewport(0, 0, game.windW, game.windH);
	// Get the viewport
    glGetIntegerv(GL_VIEWPORT, game.viewport);


}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    game.Draw();
    glutSwapBuffers();
}


static void key(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 27 :
        case 'q':
            exit(0);
            break;

    }

    glutPostRedisplay();
}

void YouSelect(int xPos, int yPos)
{
  GLint hits;

  glSelectBuffer(MAXOBJS, game.selectBuf);
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(~0);
    //exactly code from Draw

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //important thing in this method
  gluPickMatrix(xPos, game.windH - yPos, 4, 4, game.viewport);

  //glOrtho(-1, 1, 1, -1, -2, 2);
  gluPerspective(30, (float)game.windW/game.windH, 0.1, 100);
  gluLookAt(0, -1.2, 1.2, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  //glClearColor(0.0, 0.0, 0.0, 0.0);
  //glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix();
  glRotatef(game.spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(game.spin_y, -1.0f, 0.0f, 0.0f);
  game.disppole();
  glPopMatrix();
  glutSwapBuffers();
//----
  hits = glRenderMode(GL_RENDER);
  if (hits > 0) game.FixPos(game.selectBuf[(hits - 1) * 4 + 3]);
}

int old_x, old_y, moving=0;

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_RIGHT_BUTTON)
  {
    if (state == GLUT_DOWN)
    {
		moving = 1;
		old_x = x;
		old_y = y;
	}
	else if (state == GLUT_UP)
	{
        moving = 0;
    }
  }
  else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
  {
    YouSelect(x, y);
    glutPostRedisplay();
  }
}

void motion(int x, int y)
{
  int capt;
  if (moving) {
    capt = game.spin_x + x - old_x;
	//if (capt >= 65) game.spin_x = 65;
	//else if (capt <= -65) game.spin_x = -65;
	//else
	game.spin_x += x - old_x;
	capt = game.spin_y + y - old_y;
	//if (capt >= 45) game.spin_y = 45;
	//else if (capt <= -55) game.spin_y = -55;
	//else
	game.spin_y += y - old_y;
	glutPostRedisplay();
	old_x = x;
	old_y = y;
  }
}

static void idle(void)
{
    glutPostRedisplay();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 0.0f, 0.0f, 0.3f, 0.0f };

/*
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };
*/

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(10,10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Absolute game");

    game.Init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);


    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glClearColor(0.1, 0.0, 0.05, 0.0);
    //glEnable(GL_CULL_FACE); //flip normal when rotated
    //glCullFace(GL_BACK); //

    //glDepthRange(0, 10.1);
      glEnable(GL_DEPTH_TEST);
  //glDepthFunc(GL_GREATER);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);



    glutMainLoop();

    return EXIT_SUCCESS;
}
