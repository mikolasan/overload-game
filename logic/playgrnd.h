#include "../elements/package.h"
#define RANK 9

/*
*   this is logic of the game.
*/
// == playground ==
class playground : public package {
    std::vector< std::vector<bool> > pygr;		//таблица геометрии уровня

	typedef struct{				//spisok игроков
	    bool human;
		int plr;
		int chp_count;
	}listob;
	typedef std::list<listob> Glist;
	Glist gamers;

	int plyr;
	uint m,n;

	int xt, yt;
private:
    bool wait_A_moment;
    void setOrient(int x_,int y_);
	void explosion(int x_, int y_);
	void swappoints(int x1, int y1);
	void findnminus(int p, int s);
	bool PutAround(int x1, int y1);
	void ai();
	bool isAvailable(int x,int y);
	void checkPlayers();
	//bool rotation(int x, int y, int h);

public:
    //next row was needed before install relationship playgrnd<->package
	//package *pip;   //interactive array of chips. like a sparse array.

	bool isWall(uint i,uint j);

	Glist::iterator player;//global var
	void stat3(void);//useless thing

	bool nextpl();
	uint get_n();
	uint get_m();
	//конструктор
	playground();
	playground(std::string fname);
	playground(std::string fname, int poletype);
	~playground(){ /*delete pip*/; };
	//too many parametrs
//	void PutChip(int x,int y, bool &vr, int &ch, uint dd);
//	void PutChip(int x,int y, bool &vr);
	void PutChip(int x,int y);
    void PutChip(int c_num);

    void afterAnimation();
    void animationWasFinished(int x1, int y1);//slot

	//package::Decart whereis(int x1, int y1, int lev);
};
