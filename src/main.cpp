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

void YouSelect(int xPos, int yPos)
{
  glSelectBuffer(MAXOBJS, game.selectBuf);
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(~0);

  display();

  GLint hits = glRenderMode(GL_RENDER);
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
	old_x = x;
	old_y = y;
	glutPostRedisplay();
  }
}

static void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(640,480);
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
