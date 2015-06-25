#include "package.h"
#define ANGLE GL_PI/12
// == package ==
package::package(){
	//Pack = std::vector<colonn>;
	PoleSize = 0;
	v_top = Pack.begin();

	/*
	animF.b = false;
	animF.x = 0;
	animF.y = 0;
	*/
}
int package::find(int x1, int y1){
	//v_Iter p;
	//for(p=Pack.begin(); p!=Pack.end(); ++p)
	if (PoleSize!=0)
		for(uint i=0; i<PoleSize; i++)
			if (Pack[i]->hit(x1, y1)) return i;

	return -1;
}
void package::addChip(int x1, int y1, uint plr){
	int p1;					//��������� �� ���. �����
	p1 = find(x1, y1);		//��� � �����
	if (p1<0){
		colonn* w = new colonn(x1,y1,plr);
		w->addChip();
		Pack.push_back(w);
		PoleSize++;
	}
	else
		Pack[p1]->addChip();
}
void package::delChips(int x1, int y1){
	int p1;					//��������� �� ���. �����
	p1 = find(x1, y1);		//��� � �����
	if (p1<0)
		std::cout << "error:cannot delete colonn " << x1 << ' ' << y1 << " from package \n";
	else
	{
		for(int k=0; k<STARTF*2; k++)	//����� 4 ����� ������
		{
		    Pack[p1]->delChip();			//
		    std::cout << "delete chip " << k << " from colonn " << x1 << ' ' << y1 << " \n";
		}


		if (Pack[p1]->level()==0)
		{
		    std::cout << "delete colonn " << x1 << ' ' << y1 << " because of zero level \n";
			v_Iter itt = Pack.begin() + p1;
			Pack.erase(itt);
			PoleSize--;
		}
	}

}
uint package::playerNum(int x1, int y1){ //������ ���������� ����� ������
	int p1;
	p1 = find(x1, y1);//find colonn
	if (p1<0)
		return 0;
	else
		return Pack[p1]->playerNum();//that colonn has owner
}
uint package::playerNum(int x1, int y1, uint p){	//������
	int p1, p2=0;							//
	p1 = find(x1, y1);						//������� �������:
	if (p1<0){								//==1==���� ��� ������ ����
		colonn* ql = new colonn(x1,y1,p);					//������� ���������
		Pack.push_back(ql);					//� ���������� �������
		PoleSize++;
	}
	else									//==2==���� ������� �����������
		p2 = Pack[p1]->playerNum(p);			//������ ���������� ����� �����
	return p2;
}

int package::level(int x1, int y1){
	int g = this->find(x1, y1);
	//std::cout << "level: " << g->level() << "\n";
	int tmp = 0;
	if ( !(g<0) ) tmp = Pack[g]->level();
	return tmp;
}
//up to playgrnd
/*
uint package::setOrient(int x1, int y1, int h, uint d1){
	int g = this->find(x1, y1), real_h = 0;
	uint d2=0;
	if (g<0)
		std::cout << "error:cannot find colonn for orient \n";
	else
	{
        real_h = Pack[g].level() - h;
        d2 = Pack[g].setOrient(real_h, d1);
	}
	return d2;
}
*/
//down to colonn and combine in "render"
/*
float package::move(int x1, int y1, int h){
	int g = this->find(x1, y1);
	float rez;
	h = Pack[g].level() - h;
	rez = Pack[g].move(h, ANGLE);
	return rez;
}

package::Decart package::whereis(int x1, int y1, int lev){
	Decart coord;
	coord.x = coord.y = coord.z = 0;
	if(lev<0) return coord;//!
	int g = this->find(x1, y1);
	if (g>=0)
	{
	    if(Pack[g].isMoving(lev))
            this->move(x1, y1, lev);
            //!up to playgrnd
//        else
//            this->explosion(x1, y1);

        float z1,z2,z3;
        int lev_;
        Pack[g].whereis(lev, z1, z2);
        //! WTF!//
        lev_ = Pack[g].level()-lev; //up, from boots to head
        uint Dir;
        Dir = this->setOrient(x1,y1,lev_,0);
        coord.x = y1*CELLSIZE + z1*cos(GL_PI/2*Dir);	//�1,i - �������(�-���)
        coord.y = x1*CELLSIZE + z1*sin(GL_PI/2*Dir);	//�1,j - ������(�-���)
        coord.z = 0.6*FISHSIZE*(lev_-1) + z2;
        switch(Dir)
        {
            case 0:
                coord.x -= FISHSIZE;
                break;
            case 1:									//������ ��� ??
                coord.y += FISHSIZE;
                break;
            case 2:
                coord.x += FISHSIZE;
                break;
            case 3:
                coord.y -= FISHSIZE;
                break;
        }
	}

	return coord;
}


int package::animationWasFinished(int &x1, int &y1)
{
    if(!animF.empty())
    {
        animation af;
        af = animF.front();
        animF.pop_front();
        x1 = af.x;
        y1 = af.y;
        std::cout << "animation was finished: " << x1 << ' ' << y1 << '\n';
        if(animF.empty())
            return 2; //this was the last "anim"
        else
            return 1; //another
    }
    else
        return 0; // there is no animation
}
*/

void package::render()
{
    if(Pack.empty()) return;

    int obj_n=0;
    for(auto p : Pack)
	{
        int x1,y1;
	    p->getCoord(x1, y1);
	    if(!p->render(obj_n, y1*CELLSIZE, x1*CELLSIZE))
	    {
	        glutPostRedisplay();
            break;
	    }
	    obj_n++;
	}
}
void package::stat2(){		// ############ stat ############
	v_Iter p;
	int j=0;
	for(p=Pack.begin(); p!=Pack.end(); ++p){
		(*p)->stat1();
		std::cout << "===== " << j;
		std::cout << " from " << Pack.size() <<" ==========\n \n";
		j++;
	}

/*
	std::list<animation>::iterator ep;
	for(ep=animF.begin(); ep!=animF.end(); ++ep)
	{
	    std::cout << ep->x << ' ' << ep->y <<'\n';
	}
	std::cout << '\n';
	*/
}
