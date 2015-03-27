#include <list>
#include <iterator>
#pragma once

#define RANK 12

class playground{
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