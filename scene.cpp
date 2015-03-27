#include <iostream>
#include <stdio.h>
#include <conio.h>
#include <iterator>
#include "playgrnd.h"
	
//playground* doska;
//
//void disppole();
// 
//
//int main(){
//#################################
//////cheking classes base - package	
//
////	package pp;
//	package* pip = new package();
//	colonn* q = new colonn(5,7,3);
////	q->addChip();
//	
//	//q->newx = q->CurColonn.begin();q->newx.rotate(0)
//	for(int i=0; i<8; i++){
//		std::cout<< "level: " << q->level() << "\n";
//		q->addChip();
//		
//	}
//	for(int i=0; i<8; i++){
//		q->move(7-i,i/3.);
//	}
//	//q->stat1();
//	pip->addChip(2,3,1);
//	pip->stat2();
//	delete pip;
//	delete q;
//
//	return 0;
//}
//####################################
//display array
//doska = new playground("pole1");
//disppole();
//doska->nextpl();
//	  //std::cout << get_m();
//	  int x,y;
//	  for(;;){
// 		std::cin >> x >> y;
//		if (doska->give(x,y)) doska->nextpl();
//		disppole();
//		
//		std::cout << doska->player->plr; 
//		if (getch()==32) break;
//      }
//	  //doska.
//}
//
//void disppole(){
//	int l=0; 
//	package::Decart dec;
//	for (int i=0; i<=doska->get_m(); i++)
//		for (int j=0; j<=doska->get_n(); j++){
//			if (doska->isWall(i,j)) std::cout << '_';
//			else {
//				l=doska->pip->level(i,j);
//				std::cout << l;
//				while (l!=0){									
//					dec = doska->whereis(i,j,l-1);
//					l--;
//				}
//			}
//			if (j==doska->get_n()) std::cout << "\n";
//		}
//		doska->stat3();
//	
////		std::cout<<i<<' '<<j<<"\n";
//		std::cout<<"x: "<< dec.x <<"\n";
//		std::cout<<"y: "<< dec.y <<"\n";
//		std::cout<<"z: "<< dec.z <<"\n";
//}

#include <gl/glut.h>
#include <stdlib.h>
#include <time.h>
//#include <gl/gl.h>
//#include <gl/glu.h>
//#include <gl/glaux.h>
#include <math.h>



//void Reshape(int width, int height)
//{
//  glViewport(0, 0, width, height);
//  glMatrixMode(GL_PROJECTION);
//  glLoadIdentity();
//  gluOrtho2D(0, 2, 0, 2);
//  glMatrixMode(GL_MODELVIEW);
//}
#define FSIZE 0.05
#define MAXOBJS 100

//GLUquadricObj *qobj;
 playground doska("pole1");

float spin_x = 0;
float spin_y = 0;
GLint windW = 300, windH = 300;
GLint viewport[4];
GLuint selectBuf[MAXOBJS];
int n,m;

unsigned int colors[] = {
				//0x000000, 
				0x004FB2, 
				0xFFA800,
                0x72FF00,
				0xFF0030,
				0xAE00FF,
				0x00FF8A,
				0xFFAFFA
				};

		

void Init()
{
	//playground doska;
    n = doska.get_n();
	m = doska.get_m();
	doska.nextpl();
	//doska.hmuchplayer;
}


//==========
void reshape(int width, int height)
{
    windW = width;
    windH = height;
	glViewport(0, 0, windW, windH);
	// Get the viewport
    glGetIntegerv(GL_VIEWPORT, viewport);
   
}
//===========
void box(float size, float height, int corners)
{
  float r = size / 2.0, z = height;
  float alp = GL_PI/2, corn = (GL_PI*2)/corners;    
        glBegin(GL_LINE_STRIP);
		for (int pent=0; pent<=corners; pent++){
			glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(r*sin(alp), r*cos(alp), 0.0);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), 0.0);
			glVertex3f(r*sin(alp), r*cos(alp), z);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), z);
			alp += corn;
		}
        glEnd();
}
//===========
void stone(float size)
{
	float d = size/2.0;
	float md = d*0.75;
	glBegin(GL_LINE_STRIP);
		glVertex3f(d, d, 0.0);
		glVertex3f(md, md, 0.02);
		glVertex3f(md, -md, 0.02);
		glVertex3f(d, -d, 0.0);
		glVertex3f(d, d, 0.0);
		glVertex3f(-d, d, 0.0);
		glVertex3f(-md, md, 0.02);
		glVertex3f(-md, -md, 0.02);
		glVertex3f(-d, -d, 0.0);
		glVertex3f(-d, d, 0.0);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(-md, md, 0.02);
		glVertex3f(md, md, 0.02);
	glEnd();
		glBegin(GL_LINES);
		glVertex3f(-md, -md, 0.02);
		glVertex3f(md, -md, 0.02);
	glEnd();
	glBegin(GL_LINES);
		glVertex3f(-d, -d, 0.0);
		glVertex3f(d, -d, 0.0);
	glEnd();
}

//============
void disppole()
{
  GLfloat x,y,z;
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
int obj_n = 0, pl; 
unsigned int r,g,b;

for (int i=0; i<=m; i++)
	  for (int j=0; j<=n; j++){
		  /*if (doska.getcell_s(i,j)) std::cout << '_'; //check
		  else std::cout << doska.getcell_c(i,j);     //correct
		  if (j==doska.get_n()) std::cout << "\n";    //image*/
		  if (doska.isWall(i,j)) 
				{
				/*stones*/
				glPushMatrix();
				glTranslatef(0.05+0.1*j, 0.05+0.1*i, 0.0f);
				glColor3f(0.5, 0.5, 0.5);
				//glutWireCube(0.1);
				stone(0.1);
				glPopMatrix();				
		  }
		  else {
			  int co=doska.pip->level(i,j);
			  pl = doska.pip->playerNum(i,j);
			  r = colors[pl]>>16;
			  g = (colors[pl] ^ r<<16)>>8;
			  b = (colors[pl]^(r<<16 | g<<8));
			  while (co!=0)
			  {
				/*chips*/
				package::Decart dec;				
				dec = doska.whereis(i,j,co-1);
				std::cout<<i<<' '<<j<<" ("<< co-1<<")\n";
				std::cout<<"x: "<< dec.x <<"\n";
				std::cout<<"y: "<< dec.y <<"\n";
				std::cout<<"z: "<< dec.z <<"\n";
				
				glPushMatrix();
//				glTranslatef(FSIZE+0.1*j+dec.x, dec.y, 0.6*FSIZE*(co-1)+dec.z);
				//
//############# //==correct THIS line
				glTranslatef(FSIZE+dec.x, FSIZE+dec.y, dec.z);				
				glColor3ub(r,g,b);
				glLoadName(obj_n);
				//glutWireSphere(0.05f, 10, 10);
				
				box(0.1, 0.03, 8);
				glPopMatrix();
				
				co--;
			  }
		  }
		  obj_n++;
	  }
//end pole	
//  glutSwapBuffers();
  glFlush();  
}

void Draw(void)
{
	//std::cout<<"hello!";
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(-1, 1, 1, -1, -2, 2);
  gluPerspective(30, (float)windW/windH, 0.1, 100);
  gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.1, 0.0, 0.05, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glRotatef(spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(spin_y, -1.0f, 0.0f, 0.0f);
  disppole();
  glPopMatrix();
  glutSwapBuffers();
}

//===========
void ai(){
  int n1=0, n2=0;
  srand ( time(NULL) );		/*initialize random number generator*/
  if(doska.player->chp_count!=0) {
	while(!doska.give(n1,n2)){				//######## give #########
			n1 = rand()%(m+1);
			n2 = rand()%(n+1);
	}
  }
  std::cout << n1 << ' ' << n2 << "\n" ;
  doska.nextpl();
}
//===========
void FixPos(GLint h)
{
	int ti,tj;
	ti = h%(n+1);
	tj = (h-ti)/n;
	if (doska.give(tj,ti)) doska.nextpl();	//######## give #########
	while (doska.player->plr!=1) ai();
}

void YouSelect(int xPos, int yPos)
{
  GLint hits;

  glSelectBuffer(MAXOBJS, selectBuf);
  glRenderMode(GL_SELECT);
  glInitNames();
  glPushName(~0);
//exactly code from Draw
  glPushMatrix();
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //important thing in this method
  gluPickMatrix(xPos, windH - yPos, 4, 4, viewport);
   
  glOrtho(-1, 1, 1, -1, -2, 2);
  gluPerspective(30, (float)windW/windH, 0.1, 100);
  gluLookAt(0, 0, 2, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glClear(GL_COLOR_BUFFER_BIT);
  glRotatef(spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(spin_y, -1.0f, 0.0f, 0.0f);
  disppole();
  glPopMatrix();
  glutSwapBuffers();
//----
  hits = glRenderMode(GL_RENDER);
  if (hits > 0) FixPos(selectBuf[(hits - 1) * 4 + 3]);
}

int old_x, old_y, moving=0;

void mouse(int button, int state, int x, int y)
{
  if (button == GLUT_RIGHT_BUTTON) {
    if (state == GLUT_DOWN) {
		moving = 1;
		old_x = x;
		old_y = y;
	}
	else if (state == GLUT_UP) {
        moving = 0;
    }
  }
  else if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//std::cout << spin_x << ' ' << spin_y << "\n";	
	  YouSelect(x, y);
		glutPostRedisplay();
		}
}

void motion(int x, int y)
{
  int capt;
  if (moving) {
    capt = spin_x + x - old_x;
	if (capt >= 65) spin_x = 65;
	else if (capt <= -65) spin_x = -65;
	else spin_x += x - old_x;
	capt = spin_y + y - old_y;
	if (capt >= 45) spin_y = 45;
	else if (capt <= -55) spin_y = -55;
	else spin_y += y - old_y;
	glutPostRedisplay();
	old_x = x;
	old_y = y;
  }
}

void keyboard(unsigned char key, int x, int y)
{
   
   switch (key) {
      case 's':
		 doska.stat3();
         break;
	  default:
		 break;
   }
}


int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitWindowSize(800, 700);//del
  glutInitWindowPosition(600, 250);//del

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
  glutCreateWindow("Morrowind");//del

  //glutGameModeString("800x600:32");
  //glutEnterGameMode();
  Init();
  glutMotionFunc(motion);
  glutMouseFunc(mouse);

  glutReshapeFunc(reshape);
  glutDisplayFunc(Draw);
  glutKeyboardFunc(keyboard);
  glutMainLoop();
  
  return 0;
}