#include "base.h"
#include <boost/bind.hpp>
// == colonn ==
typedef std::vector<base*>::iterator b_Iter;
class colonn
{
	int x,y;

	std::vector<base*> CurColonn;
	b_Iter b_top;
	uint plr;
	int oldTimeSinceStart;
	const int animationSpeed;
	const int reserve_size;
	typedef boost::signal<void (int, int)> ContinMath;//signal type
	boost::signals::connection c;//check connection
public:
	colonn();
	colonn(int x_, int y_, uint plr_);
	~colonn(){CurColonn.clear();};

    bool animFin;
	void addChip(void);
	void delChip(void);
	uint playerNum(void);
	uint playerNum(uint pp);
	uint setOrient(int h, uint d1);
	float move(int h, float c);
	bool isMoving(int ind);
	void setMoving();
	//void whereis(int i, float &x, float &z);
	void getCoord(int &x_, int &y_);
	bool render(int obj_n, float x, float y);
	bool hit(int x_, int y_);
	int level(void);
	//
	void stat1();
	void checkAnimation();//slot
	void doContinMath(const ContinMath::slot_type& slot);//connect
	void haltContinMath();//disconnect
private:
    ContinMath continMath;//signal
};
///----


