#include <iostream>
#include <fstream>
#include <string>

#include "playgrnd.h"

#define STARTF 2
//== read play ground from file 
playground::playground(){
	gamers.clear();
	player = 0;
  
}
playground::playground(std::string fname){
	//open
  fname = fname + ".txt";
  std::ifstream pole(fname.c_str());
	//read
  char c_sym[RANK],i_sym;//special vars for reading matrix in c++ like strings
  int sym;
  listob one;		//local exhibit vector of players
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
					 one.chp_count = STARTF;
					 one.plr = plyr;
					 gamers.push_back(one);
					 pygr[m][i1].player = plyr;
					 pygr[m][i1].count = STARTF;
					 break;
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
	//listob thewho = *player;	//материализация объекта с указателя
	//int Uno = thewho.plr;		//number of current player
	if (pygr[x][y].wall ){
		return false;}
	if (pygr[x][y].player!=player->plr){
		std::cout << player->plr << ' ' << pygr[x][y].player << "\n";
		return false;}
	else {
		pygr[x][y].count++;
		player->chp_count++;
		if (pygr[x][y].count>=4) explosion(x,y);
		return true;
	}
	
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
void playground::swappoints(int x1, int y1){
	int expans = player->plr, target=0, prey=0;

	target = pygr[x1][y1].player;	//игрок на кого падет наша фишка
	if (target!=expans){			//заходим на чужие фишки
		pygr[x1][y1].player = expans;	//помечаем их номером игрока
		if(target!=0){				//если не пустое поле(там есть фишки)
			prey = pygr[x1][y1].count;	//запоминаем
			player->chp_count += prey;	//добавляем в общий счет накрытые фишки		
			findnminus(target, prey);	//вычитаем
		}
	}
}
//==========
void playground::explosion(int x_,int y_){
	int x1, y1;
	bool var, var2, rep_v=false, rep_h=false;
	pygr[x_][y_].count-=4;
	player->chp_count-=4;
	if (pygr[x_][y_].count==0) pygr[x_][y_].player=0;
	

	for (int i4=0; i4<=1; i4++){
		for (int ver=0; ver<=1; ver++){
			if (rep_h) break;
			y1=y_;	
			x1=x_-1;
			swappoints(x1,y1);
			var=give(x1,y1);
			x1=x_+1;
			swappoints(x1,y1);
			var2=give(x1,y1);
			if (var && var2) break;
			else if (!(var || var2)) rep_h=true;
		}
		for (int hor=0; hor<=1; hor++){
			if (rep_v) break;
			x1=x_;	
			y1=y_-1;
			swappoints(x1,y1);
			var=give(x1,y1);
			y1=y_+1;
			swappoints(x1,y1);
			var2=give(x1,y1);
			if (var && var2) break;
			else if (!(var || var2)) rep_v=true;
		}
		if (!(rep_h || rep_v)) break;
	
	}
}

void playground::stats(void){
	Glist::iterator man = player;
		 do{
			++man;
			std::cout << "player: " << man->plr << " have "<< man->chp_count <<"\n";	
		 }while(man!=player);
}