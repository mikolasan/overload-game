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
	int plyr,m,n;
private:
	void explosion(int x_,int y_);
	int hmuchplayer();
public:
	bool getcell_s(int i,int j);
    int getcell_g(int i,int j);
    int getcell_c(int i,int j);
	
	int player;
	void nextpl();
	int get_n();
	int get_m();
	
	void loadground(std::string fname);
	bool give(int x,int y);

};