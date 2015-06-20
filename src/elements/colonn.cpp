#include "colonn.h"
#include "params.h"

// == colonn ==
colonn::colonn(){
	x = 0;
	y = 0;
	plr = 0;
	MySize = 0;
	animFin = false;
	epoch = 0;
}
colonn::colonn(int x_, int y_, uint plr_)
{
    x = x_;
    y = y_;
    plr = plr_;
    MySize = 0;
    animFin = false;
    epoch = 0;
}

void colonn::addChip(void){
	this->MySize++;
	base* q1 = new base();
	q1->doOnDejavu( boost::bind(&colonn::setFlag, this) );
	CurColonn.push_back(q1);
	//CurColonn[CurColonn.size()-1]->doOnDejavu(Hello());
}

void colonn::delChip(void){
    if(!CurColonn.empty())
    {
        CurColonn.pop_back();
        this->MySize--;
    }
    else
        std::cout << "you wanna try to del chip from empty colonn" << std::endl;

}
uint colonn::playerNum(void){
	return plr;
}
uint colonn::playerNum(uint pp){
	this->plr = pp;
	return plr;
}

uint colonn::setOrient(int h, uint d1){
	return this->CurColonn[h]->setOrient(d1);
}

float colonn::move(int h, float c){
	return this->CurColonn[h]->rotate(c);
}
bool colonn::isMoving(int ind)
{
    /*
    if(ind>100)
    {
        std::cout << "i dont now from what place you find thi huge number!!";
        return false;
    }
    else
    */
    return CurColonn[ind]->anime;
}

void colonn::setMoving()
{
    animFin = false;
    epoch = 0;
    for(uint CSize=MySize-2*STARTF; CSize<MySize; CSize++)
        CurColonn[CSize]->anime = true;//!CurColonn[CSize]->anime;
}
/*
void colonn::whereis(int i, float &x, float &z){
	this->CurColonn[i].whereis(x, z);
}
*/
void colonn::getCoord(int &x_, int &y_)
{
    x_ = this->x;
    y_ = this->y;
}

bool colonn::render(int obj_n, float x, float y)
{

    //animFin = false;
    int r,g,b;
    r = colors[plr]>>16;
    g = (colors[plr] ^ r<<16)>>8;
    b = (colors[plr]^(r<<16 | g<<8));

    for(uint CSize=0; CSize<CurColonn.size(); CSize++)
    {
        glPushMatrix();
        glTranslatef(FISHSIZE+x, FISHSIZE+y, 0.6*FISHSIZE*CSize);
        if(this->isMoving(CSize))
        {
            uint Dir;
            Dir = this->setOrient(CSize,0);
            double ang;
            epoch += glutGet(GLUT_ELAPSED_TIME);

            if(epoch>=10*glutGet(GLUT_ELAPSED_TIME))
            {
                ang = GL_PI/50.f;
                epoch = 0;
            }
            else
            {
                ang = 0;
            }
            switch(Dir)
            {
                case 1:
                    glRotatef(-180*this->move(CSize, ang)/GL_PI, 1.0f, 0.0f, 0.0f);
                    glTranslatef(0.0, 0.0, FISHSIZE+sin(GL_PI*ang/180.));
                    break;
                case 2:
                    glRotatef(180*this->move(CSize, ang)/GL_PI, 1.0f, 0.0f, 0.0f);
                    glTranslatef(0.0, 0.0, FISHSIZE+sin(GL_PI*ang/180.));
                    break;
                case 3:
                    glRotatef(180*this->move(CSize, ang)/GL_PI, 0.0f, -1.0f, 0.0f);
                    glTranslatef(0.0, 0.0, FISHSIZE+sin(GL_PI*ang/180.));
                    break;
                case 4:
                    glRotatef(-180*this->move(CSize, ang)/GL_PI, 0.0f, -1.0f, 0.0f);
                    glTranslatef(0.0, 0.0, FISHSIZE+sin(GL_PI*ang/180.));
                    break;
            }
          //if(!this->isMoving(CSize)) animFin = true;
        }
        //for mouse selection
        glLoadName(obj_n);
        //set player color
        glColor3ub(r,g,b);
        //set material options
        glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
        glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
        this->CurColonn[CSize]->render(0.1, 0.03, 8);
        glPopMatrix();
    }
    if(animFin)
    {
        animFin = false;
        return false;
    }
    return true;
}

bool colonn::hit(int x_, int y_){
	if (x_==x && y_==y) return true;
	return false;
}
int colonn::level(void){
	//if (CurColonn.empty()) return 0;
	//else return this->CurColonn.size();
	//b_Iter b1;
	//int h = 0;
	//for(b1=CurColonn.begin(); b1!=CurColonn.end(); ++b1){
	//	if (b1==b_top) return h;
	//	else h++;
	//}
	return this->MySize;
}

void colonn::stat1(){		// ############ stat ############
	b_Iter b1;
	int i=0;
	std::cout << "-----colonn------plr: " << playerNum() <<" --------\n";
	std::cout << "x: " << this->x << "\n";
	std::cout << "y: " << this->y << "\n";
	std::cout << "-----her chips--------------\n";
	for(b1=CurColonn.begin(); b1!=CurColonn.end(); ++b1){
		std::cout << (*b1)->anime << ", ";
		//std::cout << "rot: " <<b1->rotate(0) << "; dir: " << b1->setOrient(0)<<"\n";
		i++;
	}
}

void colonn::setFlag()
{
    bool con=false;
    for(uint CSize=0; CSize<CurColonn.size(); CSize++)//MySize - 2*STARTF
    {
        con = con || isMoving(CSize);
    }
    animFin = !con;
    if(!con) //call signal
    {
        std::cout << "flag @animation in colonn " << x << ' ' << y << " @ was set" << std::endl;
        continMath(x,y);
        if(!c.connected()) std::cout << "slot not connected in colonn " << x << ' ' << y << std::endl;;
        c.disconnect();
        std::cout << "slot disconnected in colonn " << x << ' ' << y << std::endl;;
    }
}

void colonn::doContinMath(const ContinMath::slot_type& slot)
{
    c = continMath.connect(slot);
}

void colonn::haltContinMath()
{
    c.disconnect();
}
