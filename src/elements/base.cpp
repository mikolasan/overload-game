#include "base.h"

// == base ==
/*
void base::whereis(float &x, float &z){
	float r = (float)CELLSIZE/2.;
	x = r*cos(fi);
	z = r*sin(fi);
}
*/
float base::rotate(float fi_){
//	float tmp = this->fi;
	this->fi += fi_;
	if(this->fi >= GL_PI)
	{
	    this->fi = 0;
	    this->anime = false;
	    onDejavu();

	}
	return this->fi;
}

uint base::setOrient(uint d1){
	if(d1>0) {
		this->dir = d1;
		return d1;
	}
	else {
		return this->dir;
	}
}


//in earlier version  void scene::box(float size, float height, int corners)
//for replacing  base::whereis
void base::render(float size, float height, int corners)
{


        float r = size / 2.0, z = height;
        float alp = GL_PI/2, corn = (GL_PI*2)/corners;
        glBegin(GL_POLYGON);
		for (int pent=0; pent<=corners; pent++){
			glNormal3f(sin(alp+corn/2.), cos(alp+corn/2.), 0.0);
			glVertex3f(r*sin(alp), r*cos(alp), 0.0);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), 0.0);
			glVertex3f(r*sin(alp), r*cos(alp), z);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), z);
			alp += corn;
		}
        glEnd();
/*
        glColor3ub(0,10,10);
        glBegin(GL_LINE_STRIP);
		for (int pent=0; pent<=corners; pent++){
			//glNormal3f(0.0, 0.0, 1.0);
			glVertex3f(r*sin(alp), r*cos(alp), 0.0);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), 0.0);
			glVertex3f(r*sin(alp), r*cos(alp), z);
			glVertex3f(r*sin(alp+corn), r*cos(alp+corn), z);
			alp += corn;
		}
        glEnd();
        */
}

void base::doOnDejavu(const OnDejavu::slot_type& slot)
{
    onDejavu.connect(slot);
}
