#include <GL/glut.h>
#include <stdlib.h>

#include "draw/scene.h"

hbz game;

/* GLUT callback Handlers */

static void resize(int width, int height)
{
    game.reshape(width, height);
}

static void display(void)
{
    game.Draw();
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

#define MAXOBJS 512

void YouSelect(int xPos, int yPos)
{
  GLuint selectBuf[MAXOBJS];
  glSelectBuffer(MAXOBJS, selectBuf); // Specify the array to be used for the returned hit records
  glRenderMode(GL_SELECT); // Enter selection mode
  glInitNames(); // Initialize the name stack
  glPushName(0);
  // Define the viewing volume you want to use for selection
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPickMatrix(xPos, game.windH - yPos, 4, 4, game.viewport); //! important thing in this method
  gluPerspective(30, (float)game.windW/game.windH, 0.1, 100);
  gluLookAt(0, -1.2, 1.2, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glRotatef(game.spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(game.spin_y, -1.0f, 0.0f, 0.0f);
  game.render_field();
  glPopMatrix();
  glFlush();
  glutSwapBuffers();
  
  GLint hits = glRenderMode(GL_RENDER);
  std::cout << "select: " << xPos << ", " << yPos << std::endl;
  std::cout << "  hits: " << hits << std::endl;
  if (hits > 0) game.process_hits(selectBuf[(hits - 1) * 4 + 3]);

  display();
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
  //int capt;
  if (moving) {
    //capt = game.spin_x + x - old_x;
	//if (capt >= 65) game.spin_x = 65;
	//else if (capt <= -65) game.spin_x = -65;
	//else
	game.spin_x += x - old_x;
	//capt = game.spin_y + y - old_y;
	//if (capt >= 45) game.spin_y = 45;
	//else if (capt <= -55) game.spin_y = -55;
	//else
	game.spin_y += y - old_y;
	old_x = x;
	old_y = y;
	glutPostRedisplay();
  }
}

static void idle(void)
{
    glutPostRedisplay();
}
/*
static void calcposobs(void)
{
  dir[0] = sin(alpha * M_PI/180.0); //Работаем с углом поворота alpha оси X
  dir[2] = cos(alpha * M_PI/180.0) * sin(beta * M_PI/180.0); //Работаем с углом поворота alpha и beta по трем осям одновременно
  dir[1] = cos(beta * M_PI/180.0); //Работаем с Z

  obs[0] += v*dir[0];
  obs[1] += v*dir[1];
  obs[2 ]+= v*dir[2];
}
*/
/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(1024,768);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Absolute game");

    game.Init();
    
    glutReshapeFunc(resize);
    glutDisplayFunc(display);
    glutKeyboardFunc(key);
    glutIdleFunc(idle);
    glutMotionFunc(motion);
    glutMouseFunc(mouse);

    glutMainLoop();

    return EXIT_SUCCESS;
}
