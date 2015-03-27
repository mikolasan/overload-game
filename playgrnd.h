#include <list>
#include <vector>
#include <iterator>


typedef unsigned short int uint;

#define RANK 12
#define GL_PI 3.1415926535897932384626433832795028841971693993751

// == base ==
class base{
	float fi;
public:
	base(){fi=0;};
	float rotate(float fi_);
	void whereis(float &x, float &z);
};		//----

// == colonn ==
class colonn : base{
	int x,y;
	uint plr;
	std::vector<base> CurColonn;
public:
	colonn(){x=0; y=0; plr=0; CurColonn.clear();};
	colonn(int x_, int y_, uint plr_){x=x_; y=y_; plr=plr_;};

	void addChip(void);
	void move(int h);
	bool hit(int x_, int y_);
	int level(void);
};		//----

// == package ==
typedef std::vector<colonn>::iterator v_Iter;
class package : colonn{
	std::vector<colonn> Pack;
	
private:
	v_Iter find(int x1, int y1);
public:
	void addChip(int x1, int y1, uint plr);
	//del;
};		//----


// == playground ==
class playground : package{
	//element of table
    typedef struct{
		bool wall;
		int player;
        int count;
	}cell;
    cell pygr[RANK][RANK];
	
	//spisok
	typedef struct{
		int plr;
		int chp_count;
	}listob;
	typedef std::list<listob> Glist;
	Glist gamers;
	
	int plyr,m,n;
private:
	void explosion(int x_,int y_);
	void swappoints(int x1, int y1);
	void findnminus(int p, int s);
//	void store(int c);
//	void remove(listob *ob);
public:
	bool getcell_s(int i,int j);
    int getcell_g(int i,int j);
    int getcell_c(int i,int j);
	
	Glist::iterator player;//global var
	void stats(void);
	
	bool nextpl();
	int get_n();
	int get_m();
	//конструктор
	playground();
	playground(std::string fname);
	bool give(int x,int y);

};