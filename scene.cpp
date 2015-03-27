#include <iostream>
#include "playgrnd.h"
//
//
//void disppole();
 
//
//main(){
//	
//	doska.loadground("pole1");
//  
////display array
//disppole();
//	  //std::cout << get_m();
//	  int x,y;
//	  doska.player = 1;
//	  for (int ig=0; ig<=2; ig++){
//		  std::cin >> x >> y;
//		  doska.give(x,y);
//		  disppole();
//		  
//	  }
//}
//
//void disppole(){
//	for (int i=0; i<=doska.get_m(); i++)
//	  for (int j=0; j<=doska.get_n(); j++){
//		  if (doska.getcell_s(i,j)) std::cout << '_';
//		  else std::cout << doska.getcell_c(i,j);
//		  if (j==doska.get_n()) std::cout << "\n";
//	  }
//}

#include <gl/glut.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
//#include <gl/glaux.h>
//#include <math.h>

//#define GL_PI 3.1415926535897932384626433832795028841971693993751

//void Reshape(int width, int height)
//{
//  glViewport(0, 0, width, height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluOrtho2D(0, 2, 0, 2);
//  glMatrixMode(GL_MODELVIEW);
//}
#define FISHKA 1

//GLUquadricObj *qobj;
 playground doska;

float spin_x = 0;
float spin_y = 0;

//==========
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	glOrtho(-1, 1, 1, -1, -2, 2);
    gluPerspective(30, (float)width/height, 0.1, 100);
    gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
}
//===========


void disppole()
{

	GLfloat x,y,z;
  doska.loadground("pole1");
  int n = doska.get_n(),m = doska.get_m();
//draw pole! 
  //lines
  glLineWidth(2);
 glColor3f(1.0f, 1.0f, 1.0f);
glTranslatef(-((n+1)*0.1)/2, -((m+1)*0.1)/2, 0.0);
 x = 0.0f; 
for(int v=0; v<=n+1; v++){	
    glBegin(GL_LINES);
	z = 0.0f;
	y = 0.0f;
	glVertex3f(x, y, z);
	y += (m+1)*0.1;	
	glVertex3f(x, y, z);
	glEnd();
	x += 0.1f;
}
y = 0.0f;
for(int h=0; h<=m+1; h++){	
    glBegin(GL_LINES);
	x = 0.0f;
	glVertex3f(x, y, z);
	x += (n+1)*0.1;	
	glVertex3f(x, y, z);
	glEnd();
	y += 0.1f;
}  
//stone & stuff
for (int i=0; i<=m; i++)
	  for (int j=0; j<=n; j++){
		  if (doska.getcell_s(i,j)) 
				{
				glPushMatrix();
				glTranslatef(0.05+0.1*j, 0.05+0.1*i, 0.05f);
				glColor3f(0.5, 0.5, 0.5);
				glutWireCube(0.1);
				glPopMatrix();				
		  }
		  else {
			  int co=doska.getcell_c(i,j);
			  while (co!=0)
			  {
				glPushMatrix();
				glTranslatef(0.05+0.1*j, 0.05+0.1*i, 0.05f*co);
				glColor3ub(150, 0, 255);
				glutSolidSphere(0.05f, 10, 10);
				glPopMatrix();
				co--;
			  }
		  }
		  
	  }
//end pole	
  glutSwapBuffers();
  glFlush();  
}

void Draw(void)
{
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  glPushMatrix();
  glRotatef(spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(spin_y, -1.0f, 0.0f, 0.0f);
  disppole();
  glPopMatrix();
}

//===========
int old_x, old_y, moving=0;

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_LEFT_BUTTON) {
    if (state == GLUT_DOWN) {
		moving = 1;
		old_x = x;
		old_y = y;
	}
	else if (state == GLUT_UP) {
        moving = 0;
    }
  }
  else {std::cout << x;
		std::cout << y;
  }
}

void motion(int x, int y)
{
  if (moving) {
	spin_x += x - old_x;
    spin_y += y - old_y;
	glutPostRedisplay();
	old_x = x;
	old_y = y;
  }
}

int main(int argc, char *argv[])
{



  glutInit(&argc, argv);
  glutInitWindowSize(400, 300);//del
  glutInitWindowPosition(100, 100);//del

  glutInitDisplayMode(GLUT_RGB);
  glutCreateWindow("Morrowind");//del

  //glutGameModeString("800x600:32");
  //glutEnterGameMode();
  glutMotionFunc(motion);
  glutMouseFunc(mouse);

  glutReshapeFunc(reshape);
  glutDisplayFunc(Draw);
  glClearColor(0, 0, 0, 0);

  glutMainLoop();
  
  return 0;
}