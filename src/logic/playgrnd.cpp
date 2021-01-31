#include "playgrnd.h"
#include <iostream>
#include <fstream>

// == playground ==
playground::playground()
{
    gamers.clear();          //global init: list
    player = gamers.begin(); //pointer
}

playground::playground(std::string fname)
{                   // read play ground from file
    gamers.clear(); //global init: list

    n = m = plyr = 0;

    std::ifstream file(fname);
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            size_t line_size = line.size();
            std::vector<bool> pygr_row(line_size, false);
            std::vector<bool>::iterator flags = pygr_row.begin();

            int nmax = 0;
            for (std::string::iterator it = line.begin(); it != line.end(); ++it)
            {
                char sym = *it;
                switch (sym)
                {
                case '0':
                    //isWall
                    *flags = true;
                    break;
                case '1':
                    //empty cell
                    break;
                case '2':
                    //player start position
                    plyr++;
                    listob one; //local exhibit vector of players
                    one.chp_count = STARTF;
                    one.plr = plyr;
                    gamers.push_back(one);
                    for (int g = 0; g < STARTF; g++)
                        addChip(m, nmax, plyr);
                    break;
                }
                nmax++;
                flags++;
            }

            if (nmax > n)
                n = nmax;
            if (nmax > 0)
                m++;
            pygr.push_back(pygr_row);
        }
        file.close();
    }
    else
    {
        std::cout << "error: not load battleground";
    }

    player = gamers.begin();

    /*   for(int i1=0;i1<m;i1++)
    {
            for(int i2=0;i2<n;i2++)
            {
                std::cout << pygr[i1][i2];
            }
            std::cout << '\n';
    }
*/
    /*
    int nn=0;
    for(player=gamers.begin();player!=gamers.end();player++)
    {
        std::cout << "player place in list " << nn << " and have plr: " << player->plr << " and chp_count" << player->chp_count << '\n';
        nn++;
    }
*/
}

bool playground::nextpl()
{
    if (!gamers.empty())
    {
        this->player++;
        if (player == gamers.end())
            player = gamers.begin();
        return true;
    }
    return false;
}

uint playground::get_n()
{
    return n - 1;
}
uint playground::get_m()
{
    return m - 1;
}

bool playground::isWall(uint i, uint j)
{
    //std::cout << pygr[i][j];
    if (!pygr.empty() && pygr.size() > i)
        if (!pygr[i].empty() && pygr[i].size() > j)
            return pygr[i][j];

    return true;
}
//============
bool playground::isAvailable(int x, int y)
{
    int g = find(x, y);
    if (g >= 0 && Pack[g]->isMoving(Pack[g]->level() - 1))
        return false;

    uint person1 = this->playerNum(x, y);
    uint person2 = player->plr;
    if (isWall(x, y))
    { //���� ������
        return false;
    }
    else if (person1 != person2)
    { //�� ���� �����
        return false;
    }
    else
    { //��� ������, �����
        return true;
    }
}
//=========
#include <stdlib.h>
void playground::findnminus(int p, int s)
{
    Glist::iterator iter = player;
    while (iter->plr != p)
    {
        ++iter;
    }
    iter->chp_count -= s;
}
//=========
void playground::swappoints(int x1, int y1)
{   //!!���������� �������� ������
    //(��������� �� ������ player)
    int expans = player->plr, target = 0, prey = 0;

    target = this->playerNum(x1, y1); //����� �� ���� ����� ���� �����
    if (target != expans)
    {                                    //������� �� ����� �����
        this->playerNum(x1, y1, expans); //�������� �� ������� ������
        if (target != 0)
        {                               //���� �� ������ ����(��� ���� �����)
            prey = this->level(x1, y1); //����������
            player->chp_count += prey;  //��������� � ����� ���� �������� �����
            findnminus(target, prey);   //��������
        }
    }
}

bool playground::PutAround(int x1, int y1)
{
    if (!isWall(x1, y1))
    {
        PutChip(x1, y1);
        return true;
    }
    else
        return false;
}

// this method for control user's mouse clicking
void playground::PutChip(int c_num)
{
    int x, y;
    Pack[c_num]->getCoord(x, y);
    if (this->isAvailable(x, y))
    {
        //PutChip(x,y);
        int ped = player->plr;
        swappoints(x, y);
        //v-- give --v
        this->addChip(x, y, ped); //pygr[x][y].count++;
        player->chp_count++;
        int high = this->level(x, y);
        if (high >= STARTF * 2)
        {
            Pack[c_num]->doContinMath(boost::bind(&playground::animationWasFinished, this, _1, _2));
            Pack[c_num]->setMoving(); //if one add chip then "find" must work
            setOrient(x, y);
        }
        else
            this->nextpl();
    }
}

void playground::TestChip(int c_num)
{
    Pack[c_num]->setMoving();
    int x, y;
    Pack[c_num]->getCoord(x, y);
    setOrient(x, y);
}

// and this just for adding new chips
void playground::PutChip(int x, int y)
{
    int ped = player->plr;
    swappoints(x, y);
    //v-- give --v
    this->addChip(x, y, ped); //pygr[x][y].count++;
    player->chp_count++;
    int high = this->level(x, y);
    if (high >= STARTF * 2)
    {
        wait_A_moment = true;
        Pack[find(x, y)]->doContinMath(boost::bind(&playground::animationWasFinished, this, _1, _2));
        Pack[find(x, y)]->setMoving();
        setOrient(x, y);
    }

    //std::cout << "PutChip be executed in " << x << ' ' << y << std::endl;
    checkPlayers();
}

void playground::animationWasFinished(int x1, int y1) //
{
    wait_A_moment = false;
    std::cout << "explosion avaiable to be executed in " << x1 << ' ' << y1 << std::endl;
    int hh = this->level(x1, y1);
    if (xt == x1 && yt == y1)
        std::cout << "i dont understand this stupid repeat call!\n";
    else
    {
        //Pack[find(x1,y1)]->haltContinMath();
        explosion(x1, y1);
        //this->stat2();
        std::cout << "with level " << hh << std::endl
                  << " and wait for a moment is " << wait_A_moment << std::endl;
        if (!wait_A_moment)
            this->nextpl();
    }
    xt = x1;
    yt = y1;
}
//==========
void playground::explosion(int x_, int y_)
{
    //###### ����������� ���� (+PutChip)
    player->chp_count -= STARTF * 2; //one list operation
    bool var, var2, rep_v = false, rep_h = false;
    this->delChips(x_, y_); //	pygr[x_][y_].count-=4;
                            //! why 2 repeats?
    for (int i4 = 0; i4 < 2; i4++)
    {
        for (int ver = 0; ver < 2; ver++)
        { //vertical
            if (rep_h)
                break;
            //left
            var = PutAround(x_ - 1, y_);
            //right
            var2 = PutAround(x_ + 1, y_);
            if (var && var2)
                break;
            else if (!(var || var2))
                rep_h = true;
        }
        for (int hor = 0; hor < 2; hor++)
        { //horizontal
            if (rep_v)
                break;
            //up
            var = PutAround(x_, y_ - 1);
            //down
            var2 = PutAround(x_, y_ + 1);
            if (var && var2)
                break;
            else if (!(var || var2))
                rep_v = true;
        }
        if (!(rep_h || rep_v))
            break;
    }
}
//============
//==========
void playground::setOrient(int x_, int y_)
{
    //###### ������ �����������
    bool var, var2, rep_v = false, rep_h = false;
    int ch = this->level(x_, y_) - 1; //h
    for (int i4 = 0; i4 < 2; i4++)
    {
        for (int ver = 0; ver < 2; ver++)
        { //vertical
            if (rep_h)
                break;
            //left
            var = !isWall(x_ - 1, y_);
            if (var && ch >= 0)
                Pack[find(x_, y_)]->setOrient(ch--, 1);
            //right
            var2 = !isWall(x_ + 1, y_);
            if (var2 && ch >= 0)
                Pack[find(x_, y_)]->setOrient(ch--, 2);
            if (var && var2)
                break;
            else if (!(var || var2))
                rep_h = true;
        }
        for (int hor = 0; hor < 2; hor++)
        { //horizontal
            if (rep_v)
                break;
            //up
            var = !isWall(x_, y_ - 1);
            if (var && ch >= 0)
                Pack[find(x_, y_)]->setOrient(ch--, 3);
            //down
            var2 = !isWall(x_, y_ + 1);
            if (var2 && ch >= 0)
                Pack[find(x_, y_)]->setOrient(ch--, 4);
            if (var && var2)
                break;
            else if (!(var || var2))
                rep_v = true;
        }
        if (!(rep_h || rep_v))
            break;
    }
}

void playground::stat3(void)
{
    Glist::iterator man = player;
    do
    {
        ++man;
        std::cout << "player: " << man->plr << " have " << man->chp_count << "\n";
    } while (man != player);
    this->stat2();
}

void playground::ai()
{
    int n1 = 0, n2 = 0, R;
    srand(time(NULL)); //== initialize random number generator ==/
    if (this->player->chp_count != 0)
    {
        while (!this->isAvailable(n1, n2))
        { //######## give #########
            R = rand() % Pack.size();
            Pack[R]->getCoord(n1, n2);
        }
    }
    std::cout << "ai work: " << n1 << ' ' << n2 << "\n";
    this->PutChip(R);
    if (this->nextpl())
        std::cout << "next turn.\n";
    else
        std::cout << "all players are dead.\n";
}

void playground::checkPlayers()
{
    int nn = 0;
    if (!gamers.empty())
    {
        for (Glist::iterator iter = gamers.begin(); iter != gamers.end(); ++iter)
        {
            std::cout << "player place in list " << nn << " and have plr: " << iter->plr << " and chp_count" << iter->chp_count << '\n';
            if (iter->chp_count == 0)
            {
                std::cout << "player " << iter->plr << " lose";
                gamers.erase(iter);
                iter = gamers.begin();
            }
            nn++;
        }
        if (gamers.size() == 1)
        {
            std::cout << "player " << gamers.begin()->plr << " win\ngame over\n";
            //gamers.clear();
        }
    }
}
