#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <math.h>

#include "playgrnd.h"

#define CELLSIZE 0.1
#define FISHSIZE 0.05
#define STARTF 2

// == base ==
void base::whereis(float &x, float &z){
	float r = (float)CELLSIZE/2.;
	x = r*cos(fi);
	z = r*sin(fi);
}
float base::rotate(float fi_){
//	float tmp = this->fi;
	this->fi += fi_;
	return this->fi;
}
uint base::orient(uint d1){
	if(d1>0) {
		this->dir = d1;
		return d1;
	}
	else {
		return this->dir;
	}
}
// == colonn ==
colonn::colonn(){
	x = 0; 
	y = 0; 
	plr = 0;
	MySize = 0;
	//CurColonn = std::vector<base> (1);
	//b_top = CurColonn.begin();
}

void colonn::addChip(void){
	this->MySize++;
	//MySize++;
	base q1;
/*	if (b_top!=CurColonn.end())
		*b_top = q1;
	else*/
	CurColonn.push_back(q1);
	/*uint s;
	s = CurColonn.size();
	CurColonn.resize(s+1);
	*/
	//++b_top;
}
void colonn::delChip(void){
	CurColonn.pop_back();
	this->MySize--;
}
uint colonn::playerNum(void){
	return plr;
}
uint colonn::playerNum(uint pp){
	this->plr = pp;
	return plr;
}
uint colonn::orient(int h, uint d1){
	return this->CurColonn[h].orient(d1);
}
float colonn::move(int h, float c){
	return this->CurColonn[h].rotate(c);
}
void colonn::whereis(int i, float &x, float &z){
	this->CurColonn[i].whereis(x, z);
}

bool colonn::hit(int x_, int y_){
	bool answer = false;
	if (x_==x && y_==y) answer = true;
	return answer;
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
		std::cout << i << ": ";
		std::cout << "rot: " <<b1->rotate(0) << "; dir: " << b1->orient(0)<<"\n";
		i++;
	}
}

// == package ==
package::package(){
	//Pack = std::vector<colonn>;
	PoleSize = 0;
	v_top = Pack.begin();
}
int package::find(int x1, int y1){
	//v_Iter p;					
	//for(p=Pack.begin(); p!=Pack.end(); ++p)
	if (PoleSize!=0)
		for(int i=0; i<PoleSize; i++)
			if (Pack[i].hit(x1, y1)) return i;
	
	return -1;	
}
void package::addChip(int x1, int y1, uint plr){
	int p1;					//указатель на сущ. столб
	p1 = find(x1, y1);		//или в конец
	if (p1<0){
		colonn w(x1,y1,plr);
		w.addChip();
		Pack.push_back(w);
		PoleSize++;
		//Pack[PoleSize].addChip();
	}
	else 
		Pack[p1].addChip();
}
void package::delChip(int x1, int y1){
	int p1;					//указатель на сущ. столб
	p1 = find(x1, y1);		//или в конец
	if (p1<0)
		std::cout << "error:cannot delete colonn from package \n";
	else 
	{
		for(int k=0; k<STARTF*2; k++)	//снять 4 фишки сверху
			Pack[p1].delChip();			//
		
		if (Pack[p1].level()==0) {
			v_Iter itt = Pack.begin() + p1;		
			Pack.erase(itt);
			PoleSize--;
		}
	}		

}
uint package::playerNum(int x1, int y1){ //только показывает номер игрока
	int p1, p2=0;					
	p1 = find(x1, y1);		
	if (p1<0)
		;//std::cout << "error:cannot show player number \n";
	else
		p2 = Pack[p1].playerNum();			//
	return p2;
}
uint package::playerNum(int x1, int y1, uint p){	//меняет
	int p1, p2=0;							//
	p1 = find(x1, y1);						//находим столбец:
	if (p1<0){								//==1==если это пустое поле
		colonn ql(x1,y1,p);					//создаем контейнер
		Pack.push_back(ql);					//с правильным идентом
		PoleSize++;
	}
	else									//==2==если столбец существовал
		p2 = Pack[p1].playerNum(p);			//просто записываем новый идент
	return p2;	
}

int package::level(int x1, int y1){
	int g = this->find(x1, y1);
	//std::cout << "level: " << g->level() << "\n";
	int tmp = 0;
	if ( !(g<0) ) tmp = Pack[g].level();
	return tmp;
}

uint package::orient(int x1, int y1, int h, uint d1){
	int g = this->find(x1, y1), real_h = 0;
	uint d2=0;
	if (g<0)
		std::cout << "error:cannot find colonn for orient \n";
	else {
	real_h = Pack[g].level() - h;
	d2 = Pack[g].orient(real_h, d1);
	}
	return d2;
}

float package::move(int x1, int y1, int h, float c){
	int g = this->find(x1, y1);
	float rez;
	h = Pack[g].level() - h;
	rez = Pack[g].move(h, c);
	return rez;
}

package::Decart package::whereis(int x1, int y1, int lev){
	Decart coord;
	float z1,z2,z3;
	int g = this->find(x1, y1);
	
	if ( !(g<0) ) 
		Pack[g].whereis(lev, z1, z2);

	lev = Pack[g].level()-lev;
	uint Dir;
	Dir = this->orient(x1,y1,lev,0);
	coord.x = y1*CELLSIZE + z1*cos(GL_PI/2*Dir);	//х1,i - столбцы(у-ось)
	coord.y = x1*CELLSIZE + z1*sin(GL_PI/2*Dir);	//у1,j - строки(х-ось)
	coord.z = 0.6*FISHSIZE*(lev-1) + z2;
	switch(Dir){
		case 0:
			coord.x -= FISHSIZE;
			break;
		case 1:									//лишний код ??
			coord.y += FISHSIZE;
			break;
		case 2:
			coord.x += FISHSIZE;
			break;
		case 3:
			coord.y -= FISHSIZE;
			break;
	}
	return coord;
}

void package::stat2(){		// ############ stat ############
	v_Iter p;				
	int j=0;
	for(p=Pack.begin(); p!=Pack.end(); ++p){
		p->stat1();
		std::cout << "===== " << j;
		std::cout << " from " << Pack.size() <<" ==========\n \n";
		j++;
	}
}

// == playground ==
playground::playground(){
  gamers.clear();			//global init: list
  pip = new package();		//vector of chips
  anim.b = false;
}

playground::playground(std::string fname){// read play ground from file 
  gamers.clear();			//global init: list
  pip = new package();		//vector of chips
  anim.b = false;

  char c_sym[RANK],i_sym;	//special vars for reading matrix in c++ like strings
  int sym, times;
  listob one;				//local exhibit vector of players
  plyr = 0; m = 0; n = 0;
  
  fname = fname + ".txt";	
  std::ifstream field(fname.c_str());//open
  if(field.is_open())
  {
        std::string line;
        while(std::getline(field, line))
        {
              n = line.length();
              std::istringstream iss(line);
              int sym;
              for (int i1=0; i1<=n; i1++)
              {
                    iss >> sym;
                    times = 0;				//default values
                    pygr[m][i1] = false;	//&
                    switch (sym)
                    {
                       case 0 :
                         //isWall
                         pygr[m][i1] = true;
                         break;
                       case 1 :
                         //empty cell
                         break;
                       case 2 :
                         //player start position
                         plyr++;
                         one.chp_count = STARTF;
                         one.plr = plyr;
                         gamers.push_back(one);
                         times = STARTF;
                         break;
                    }
                    for (int g=0; g<times; g++)
		                pip->addChip(m, i1, plyr);
              }
        }
        m++;
  }
  player = gamers.end();
}
//========

bool playground::nextpl(){
	Glist::iterator thewho = player;
	if (!gamers.empty()){
		if(player == gamers.end()) player = gamers.begin();
		else if(++thewho == gamers.end()) player = gamers.begin();
		else ++player;
		return true;
	}
    return false;
}

int playground::get_n(){
	return n-1;
}
int playground::get_m(){
	return m-1;
}

bool playground::isWall(int i,int j){
	return pygr[i][j];
}
//============
bool playground::give(int x,int y){
	if(!this->anim.b) {
		uint person1 = pip->playerNum(x, y);
		int person2 = player->plr;
		//std::cout << "trying give to "<<x<<" "<<y<<"\n" ;
		if (pygr[x][y]){				//тупо стенка	
			//std::cout << "1false \n" ;
			return false;}
		if (person1!=person2){			//не свой игрок
			//std::cout << "2false \n" ;
			//std::cout << player->plr << ' ' << pygr[x][y].player << "\n";
			return false;}
		else {							//все хорошо, тогда
			//this->stat3();
			//std::cout << "3true \n" ;
			
			return true;
		}
	}
	else 
		return false;
}
//=========
void playground::findnminus(int p, int s){
	Glist::iterator iter = player;
    while(iter->plr!=p){
		++iter;
	}
	iter->chp_count -=s;
	if(iter->chp_count==0) {
		std::cout<<"someone win";
		gamers.erase(iter);
	}
}
//=========
void playground::swappoints(int x1, int y1){	//!!использует текущего игрока
												//(указатель на список player)
	int expans = player->plr, target=0, prey=0;

	target = pip->playerNum(x1, y1);	//игрок на кого падет наша фишка
	if (target!=expans){				//заходим на чужие фишки
		pip->playerNum(x1, y1, expans);	//помечаем их номером игрока
		if(target!=0){					//если не пустое поле(там есть фишки)
			prey = pip->level(x1, y1);	//запоминаем
			player->chp_count += prey;	//добавляем в общий счет накрытые фишки		
			findnminus(target, prey);	//вычитаем
		}
	}
}
//==========
bool playground::rotation(int x, int y, int h){
	float ctrl=0;
	//do{
		ctrl = pip->move(x, y, h, GL_PI/12);
	//}while(ctrl<=GL_PI*2);
	
	if(ctrl<=GL_PI*2)
		return true;
	else 
		this->pip->stat2(); // for debug
		return false;
}
//==========
package::Decart playground::whereis(int x1, int y1, int lev){
	package::Decart coord;
	int a,b;
	if(anim.b) {
		a = 1;
		anim.b = this->rotation(anim.x, anim.y, lev);
		if (anim.b) b = 1;
		else b = 0;
		if ( (b-a)<0 ) 
			this->explosion(anim.x, anim.y);
	}
	coord = pip->whereis(x1, y1, lev);
	return coord;
}
//==========
void playground::mustGive(int x, int y, bool &vr){
	int ped = player->plr;
	if (!this->isWall(x,y) || vr){
		swappoints(x,y);
		//v-- give --v
		pip->addChip(x,y, ped);//pygr[x][y].count++;
		player->chp_count++;
		int high = pip->level(x, y);
		if (high >= STARTF*2) {
			//explosion(x,y);
			anim.b = true;
			anim.x = x;
			anim.y = y;
		}
		//^-- give --^
		vr = give(x,y);

	}
	else vr = false;
}
//==========
uint playground::orient(int x1, int y1, int &h, uint d1){
	int rx, ry, dd=0;
	if(give(x1,y1)){ 
		rx = x1 + int(cos(GL_PI/2.*d1));
		ry = y1 + int(sin(GL_PI/2.*d1));
		dd = pip->orient(rx,ry,h,d1);
	h++;
	}
	return dd;
}
//==========
void playground::explosion(int x_,int y_){
//###### пересчитать поле (+mustGive)
	player->chp_count-=STARTF*2;	//one list operation
	int x1, y1;						//--v--explosion--v--
	bool var, var2, rep_v=false, rep_h=false;
	pip->delChip(x_,y_);			//	pygr[x_][y_].count-=4;//
/*
		try{
//			pip->orient(x,y,ch,dd);
		}
		catch(...){
			std::cout<<"you are in Catch";
		}
		ch++;	
*/
//###### узнать направления	
	uint dd;					//direction of moving
	int ch = 1;						//h
	for (int i4=0; i4<2; i4++){
		for (int ver=0; ver<2; ver++){	//vertical
			if (rep_h) break;
			y1=y_;	
			x1=x_-1;					//left
			dd = 2;
			orient(x1,y1,ch,dd);
			x1=x_+1;					//right
			dd = 0; 
			orient(x1,y1,ch,dd);
			if (var && var2) break;
			else if (!(var || var2)) rep_h=true;
		}
		for (int hor=0; hor<2; hor++){	//horizontal
			if (rep_v) break;
			x1=x_;	
			y1=y_-1;					//up
			dd = 1;
			orient(x1,y1,ch,dd);
			y1=y_+1;					//down
			dd = 3;
			orient(x1,y1,ch,dd);
			if (var && var2) break;
			else if (!(var || var2)) rep_v=true;
		}
		if (!(rep_h || rep_v)) break;
	
	}
}

void playground::stat3(void){
	Glist::iterator man = player;
		 do{
			++man;
			std::cout << "player: " << man->plr << " have "<< man->chp_count <<"\n";	
		 }while(man!=player);
	this->pip->stat2();
}
