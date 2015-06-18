#include <list>
#include <vector>
#include <iterator>
#include <sys/types.h>

//typedef unsigned short int uint;

#define RANK 12
#define GL_PI 3.1415926535897932384626433832795028841971693993751

// == base ==
class base{
	float fi;
	uint dir;
public:
	base(){fi=0; dir=0;};
	float rotate(float fi_);
	uint orient(uint d1);
	void whereis(float &x, float &z);
};		//----

// == colonn ==
typedef std::vector<base>::iterator b_Iter;
class colonn : public base{
	int x,y;
	uint MySize;
	
	std::vector<base> CurColonn;
	b_Iter b_top;
	uint plr;
public:	
	colonn();
	colonn(int x_, int y_, uint plr_){x=x_; y=y_; plr=plr_;MySize = 0;};
	~colonn(){CurColonn.clear();};

	void addChip(void);
	void delChip(void);
	uint playerNum(void);
	uint playerNum(uint pp);
	uint orient(int h, uint d1);
	float move(int h, float c);
	void whereis(int i, float &x, float &z);
	bool hit(int x_, int y_);
	int level(void);
	//
	void stat1();
};		//----

// == package ==
typedef std::vector<colonn>::iterator v_Iter;
class package : public colonn{
	std::vector<colonn> Pack;
	
private:
	uint PoleSize;
public:
	typedef struct{				//координата
		float x,y,z;
	}Decart;
	int find(int x1, int y1);
	v_Iter v_top;
	package();
	~package(){Pack.clear();};
	void addChip(int x1, int y1, uint plr);
	void delChip(int x1, int y1);
	uint playerNum(int x1, int y1);
	uint playerNum(int x1, int y1, uint p);
	int level(int x1, int y1);
	uint orient(int x1, int y1, int h, uint d1);
	float move(int x1, int y1, int h, float c);
	Decart whereis(int x1, int y1, int lev);
	//
	void stat2();
};		//----


// == playground ==
class playground {
    bool pygr[RANK][RANK];		//таблица геометрии уровня
	
	typedef struct{				//spisok игроков
		int plr;
		int chp_count;
	}listob;
	typedef std::list<listob> Glist;
	Glist gamers;
	
	typedef struct{				//
		bool b;
		int x,y;
	}animation;
	animation anim;

	int plyr,m,n;
private:
	void explosion(int x_, int y_);
	void swappoints(int x1, int y1);
	void findnminus(int p, int s);
	uint orient(int x1, int y1, int &h, uint d1);
	bool rotation(int x, int y, int h);
	
public:
	package *pip;
	bool isWall(int i,int j);
    
	Glist::iterator player;//global var
	void stat3(void);//useless thing
	
	bool nextpl();
	int get_n();
	int get_m();
	//конструктор
	playground();
	playground(std::string fname);
	~playground(){ delete pip; };
	void mustGive(int x,int y, bool &vr);
	//void mustGive(int x,int y, bool &vr, int &ch, uint dd);
	bool give(int x,int y);
	package::Decart whereis(int x1, int y1, int lev);
};
