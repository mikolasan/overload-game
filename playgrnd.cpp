#include <iostream>
#include <fstream>
#include <string>
#include "playgrnd.h"

//== read play ground from file 
void playground::loadground(std::string fname){
	//open
  fname = fname + ".txt";
  std::ifstream pole(fname.c_str());
	//read
  char c_sym[RANK],i_sym;
  int sym;
  plyr = 0; m = 0; n = 0;
    //init array of playground
  while (! pole.eof()){ 
		 pole.getline(c_sym,RANK);
		 n=pole.gcount();
		 for (int i1=0; i1<=n; i1++){
			 i_sym = c_sym[i1];
			 sym = atoi(&i_sym);
			 pygr[m][i1].wall = false;
			 switch (sym){
				 case 0 :
					 pygr[m][i1].wall = true;
					 break;
				 //= next line: need?
				 case 1 :
					 pygr[m][i1].count = 0;
					 break;
				 case 2 :
					 plyr++;
					 pygr[m][i1].player = plyr;
					 pygr[m][i1].count = 2;
					 break;
			 }
		 }
		 m++;

  }
}
//========
int playground::hmuchplayer(){
	return plyr;
}
void playground::nextpl(){
	if (player==hmuchplayer()) player=0;
	else player++;
}


int playground::get_n(){
	return n-1;
}
int playground::get_m(){
	return m-1;
}

bool playground::getcell_s(int i,int j){
	return pygr[i][j].wall;
}
int  playground::getcell_g(int i,int j){
	return pygr[i][j].player;
}
int  playground::getcell_c(int i,int j){
	return pygr[i][j].count;
}


//============
bool playground::give(int x,int y){
	if (pygr[x][y].wall || pygr[x][y].player!=player)
		return false;
	else {
		pygr[x][y].count++;
		if (pygr[x][y].count>=4) explosion(x,y);
		return true;
	}
	
}

void playground::explosion(int x_,int y_){
	int x1, y1;
	bool var, var2, rep_v=false, rep_h=false;
	pygr[x_][y_].count-=4;
	if (pygr[x_][y_].count==0) pygr[x_][y_].player=0;
	
	for (int i4=0; i4<=1; i4++){
		for (int ver=0; ver<=1; ver++){
			if (rep_h) break;
			y1=y_;	
			x1=x_-1;
			pygr[x1][y1].player=player;
			var=give(x1,y1);
			x1=x_+1;
			pygr[x1][y1].player=player;
			var2=give(x1,y1);
			if (var && var2) break;
			else if (!(var || var2)) rep_h=true;
		}
		for (int hor=0; hor<=1; hor++){
			if (rep_v) break;
			x1=x_;	
			y1=y_-1;
			pygr[x1][y1].player=player;
			var=give(x1,y1);
			y1=y_+1;
			pygr[x1][y1].player=player;
			var2=give(x1,y1);
			if (var && var2) break;
			else if (!(var || var2)) rep_v=true;
		}
		if (!(rep_h || rep_v)) break;
	
	}
}
