#include "scene.h"

    /*
    *  Constructor
    */
hbz::hbz(){
    doska = new playground("field1.txt");
    n = doska->get_n();
	m = doska->get_m();
    epoch = 0;
    spin_x = 0;
    spin_y = 0;
    windW = 640;
    windH = 480;
    moving=0;
};
    /*
    *  Destructor
    */
hbz::~hbz()
{
    delete doska;
}

void hbz::Init()
{
    glClearColor(0.04, 0.06, 0.21, 0.0);
    //glEnable(GL_CULL_FACE); //flip normal when rotated
    //glCullFace(GL_BACK); //

    glEnable(GL_DEPTH_TEST);
    //glDepthRange(0, 10.1);
    //glDepthFunc(GL_GREATER);

    glEnable(GL_NORMALIZE);
    
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

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, 1);
    
    glEnable(GL_COLOR_MATERIAL);
}


//===========
void hbz::stone(float size)
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
void hbz::disppole()
{

  GLfloat x,y,z;
  //lines
  glLineWidth(2);
  glColor3f(1.0f, 1.0f, 1.0f);
  glTranslatef(-((n+1)*0.1)/2, -((m+1)*0.1)/2, 0.0);
  x = 0.0f;
    for(uint v=0; v<=n+1; v++)
    {
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
    for(uint h=0; h<=m+1; h++)
    {
        glBegin(GL_LINES);
        x = 0.0f;
        glVertex3f(x, y, z);
        x += (n+1)*0.1;
        glVertex3f(x, y, z);
        glEnd();
        y += 0.1f;
    }
    //stone & stuff
    /*stones*/
    for (uint i=0; i<=m; i++)
        for (uint j=0; j<=n; j++)
        {
            if (doska->isWall(i,j))
            {
                glPushMatrix();
                glTranslatef(0.05+0.1*j, 0.05+0.1*i, 0.0f);
                glColor3f(0.5, 0.5, 0.5);
                stone(0.1);
                glPopMatrix();
            }

        }
    /* chips */
    doska->render();
}

void hbz::Draw(void)
{
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  //glOrtho(-1, 1, 1, -1, -2, 2);//this opponent to next row
  gluPerspective(30, (float)windW/windH, 0.1, 100);
  //gluLookAt(0, 0, 1.0, 2.0, 4.0, -3.0, 2.0, 2.0, -1.0);
  gluLookAt(0, -1.2, 1.2, 0, 0, 0, 0, 1, 0);
  glMatrixMode(GL_MODELVIEW);
  //glClearColor(0.1, 0.0, 0.05, 0.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix();
  glRotatef(spin_x, 0.0f, 1.0f, 0.0f);
  glRotatef(spin_y, -1.0f, 0.0f, 0.0f);

  this->disppole();

  const GLfloat light_position[] = { 0.0f, 1.0f, 0.3f, 0.0f };
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glPopMatrix();
  glFlush();
  glutSwapBuffers();
}

void hbz::reshape(int width, int height)
{
    windW = width;
    windH = height;
	glViewport(0, 0, windW, windH);
    glGetIntegerv(GL_VIEWPORT, viewport);
}

//===========
// this is logic method ->playground
/*
void hbz::ai(){
  int n1=0, n2=0;
  srand ( time(NULL) );		//== initialize random number generator ==/
  if(doska->player->chp_count!=0)
  {
	while(!doska->isAvailable(n1,n2))
	{				//######## give #########
			n1 = rand()%(m+1);
			n2 = rand()%(n+1);
	}
  }
  std::cout << "ai work: " << n1 << ' ' << n2 << "\n" ;
  doska->PutChip(n1, n2);
  if(doska->nextpl()) std::cout << "next turn.\n";
  else std::cout << "all players are dead.\n";
}
*/
//===========
void hbz::process_hits(GLint h)
{
    std::cout << "fix pos: " << h << std::endl;
    if(h>=0) doska->PutChip(h);
}


