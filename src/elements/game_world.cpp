#include "game_world.h"
#include <fstream>
#include <iostream>

GameWorld::GameWorld() {}

GameWorld::~GameWorld() {}

void GameWorld::setup() {
  read_level_map("field1.txt");
}

void update(const std::unique_ptr<Input>& input) {
  running = true;
  while (running) {
    int key = input->wait_for_key();
    if (key != ERR) {
      switch(key) {

      }
    }
  }
}

void loop() {

}

void GameWorld::read_level_map(std::string level_file) {
  std::ifstream file(level_file);
  if(!file.is_open()) {
    std::cerr << "error loading battleground";
    return;
  }

  std::string line;
  while(std::getline(file, line)) {
    size_t line_size = line.size();
    std::vector<bool> row(line_size, false);
    std::vector<bool>::iterator flags = row.begin();

    // int nmax = 0;
    for(auto it = line.begin(); it != line.end(); ++it) {
      char sym = *it;
      switch (sym) {
      case '0' :
        //isWall
        *flags = true;
        break;
      case '1' :
        //empty cell
        break;
      case '2' :
        //player start position
        // plyr++;
        // listob one;				//local exhibit vector of players
        // one.chp_count = STARTF;
        // one.plr = plyr;
        // gamers.push_back(one);
        // for (int g = 0; g < STARTF; g++)
        //   addChip(m, nmax, plyr);
        break;
      }
      // nmax++;
      flags++;
    }

    // if(nmax > n) n = nmax;
    // if(nmax > 0) m++;
    level_map.push_back(row);
  }
  file.close();
}