#include "colonn.h"
// == package ==
typedef std::vector<colonn*>::iterator v_Iter;
class package
{

protected:
	std::vector<colonn*> Pack;

    typedef struct{				//animation part
		bool b;
		int x,y;
	}animation;
	std::list<animation> animF;

private:
	uint PoleSize;
public:
//	typedef struct{				//
//		float x,y,z;
//	}Decart;
	int find(int x1, int y1);
	v_Iter v_top;
	package();
	~package(){Pack.clear();};
	void addChip(int x1, int y1, uint plr);
	void delChips(int x1, int y1);
	uint playerNum(int x1, int y1);
	uint playerNum(int x1, int y1, uint p);
	int level(int x1, int y1);
//	uint setOrient(int x1, int y1, int h, uint d1);
//	float move(int x1, int y1, int h);

	//	Decart whereis(int x1, int y1, int lev);
    void render();
	//
	void stat2();
};
		//----
