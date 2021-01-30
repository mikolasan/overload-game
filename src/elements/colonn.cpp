#include "colonn.h"
#include "params.h"

// == colonn ==
colonn::colonn() : animationSpeed(100), reserve_size(6)
{
  x = 0;
  y = 0;
  plr = 0;
  animFin = false;
  oldTimeSinceStart = 0;
  CurColonn.reserve(reserve_size);
}
colonn::colonn(int x_, int y_, uint plr_) : animationSpeed(100), reserve_size(6)
{
  x = x_;
  y = y_;
  plr = plr_;
  animFin = false;
  oldTimeSinceStart = 0;
  CurColonn.reserve(reserve_size);
}

void colonn::addChip(void)
{
  base *q1 = new base();
  q1->doOnDejavu(boost::bind(&colonn::checkAnimation, this));
  CurColonn.push_back(q1);
  //CurColonn[CurColonn.size()-1]->doOnDejavu(Hello());
}

void colonn::delChip(void)
{
  if (!CurColonn.empty())
  {
    CurColonn.pop_back();
  }
  else
    std::cout << "you wanna try to del a chip from empty colonn" << std::endl;
}
uint colonn::playerNum(void)
{
  return plr;
}
uint colonn::playerNum(uint pp)
{
  this->plr = pp;
  return plr;
}

uint colonn::setOrient(int h, uint d1)
{
  return this->CurColonn[h]->setOrient(d1);
}

float colonn::move(int h, float c)
{
  return this->CurColonn[h]->rotate(c);
}
bool colonn::isMoving(int ind)
{
  return CurColonn[ind]->anime;
}

void colonn::setMoving()
{
  animFin = false;
  oldTimeSinceStart = glutGet(GLUT_ELAPSED_TIME);
  for (auto b : CurColonn)
    b->anime = true;
  std::cout << "setMoving\n";
}
/*
void colonn::whereis(int i, float &x, float &z){
	this->CurColonn[i].whereis(x, z);
}
*/
void colonn::getCoord(int &x_, int &y_)
{
  x_ = this->x;
  y_ = this->y;
}

bool colonn::render(int obj_n, float x, float y)
{
  int r, g, b;
  r = colors[plr] >> 16;
  g = (colors[plr] ^ r << 16) >> 8;
  b = (colors[plr] ^ (r << 16 | g << 8));

  float ang = .0;
  int timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
  int deltaTime = timeSinceStart - oldTimeSinceStart;

  if (deltaTime >= animationSpeed)
  {
    ang = GL_PI / 50.f;
    oldTimeSinceStart = timeSinceStart;
  }

  for (int CSize = 0; CSize < level(); CSize++)
  {
    glPushMatrix();
    glTranslatef(FISHSIZE + x, FISHSIZE + y, 0.6 * FISHSIZE * 0); // center
    if (this->isMoving(CSize))
    {
      uint Dir = this->setOrient(CSize, 0);
      float progress = move(CSize, ang) / GL_PI; // [0, 1]
      float new_angle = 180. * progress;
      float new_z = sin(GL_PI * progress);
      float new_y = FISHSIZE * progress;
      float new_x = new_y;
      switch (Dir)
      {
      case 4: //down
        glRotatef(new_angle, 0.0f, -1.0f, 0.0f);
        glTranslatef(-2 * FISHSIZE, 0.0, 0.0);
        //glTranslatef(0.0, new_y, new_z);
        break;
      case 3: //up
        glRotatef(new_angle, 0.0f, 1.0f, 0.0f);
        glTranslatef(2 * FISHSIZE, 0.0, 0.0);

        //glTranslatef(0.0, -new_y, new_z);
        break;

      case 1: //left
        glRotatef(new_angle, -1.0f, 0.0f, 0.0f);
        glTranslatef(0.0, -2 * FISHSIZE, 0.0);
        //glTranslatef(-new_x, 0.0, new_z);
        break;
      case 2: //right
        glRotatef(new_angle, 1.0f, 0.0f, 0.0f);
        glTranslatef(0.0, 2 * FISHSIZE, 0.0);
        //glTranslatef(new_x, 0.0, new_z);
        break;
      }
    }

    glLoadName(obj_n);   //for mouse selection
    glColor3ub(r, g, b); //set player color
    //set material options
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    this->CurColonn[CSize]->render(0.1, 0.03, 8);
    glPopMatrix();
  }
  if (animFin)
  {
    animFin = false;
    std::cout << "render, animFin=" << animFin << '\n';
    return false;
  }
  return true;
}

bool colonn::hit(int x_, int y_)
{
  if (x_ == x && y_ == y)
    return true;
  return false;
}
int colonn::level(void)
{
  return CurColonn.size();
}

void colonn::stat1()
{ // ############ stat ############
  b_Iter b1;
  int i = 0;
  std::cout << "-----colonn------plr: " << playerNum() << " --------\n";
  std::cout << "x: " << this->x << "\n";
  std::cout << "y: " << this->y << "\n";
  std::cout << "-----her chips--------------\n";
  for (b1 = CurColonn.begin(); b1 != CurColonn.end(); ++b1)
  {
    std::cout << (*b1)->anime << ", ";
    //std::cout << "rot: " <<b1->rotate(0) << "; dir: " << b1->setOrient(0)<<"\n";
    i++;
  }
}

void colonn::checkAnimation()
{
  bool animated = false;
  for (int CSize = 0; CSize < level(); CSize++)
  {
    animated = animated || isMoving(CSize);
  }

  animFin = !animated;
  std::cout << "checkAnimation, animFin=" << animFin << '\n';
  if (animFin) //call signal
  {
    std::cout << "flag @animation in colonn " << x << ' ' << y << " @ was set" << std::endl;
    continMath(x, y);
    if (!c.connected())
      std::cout << "slot not connected in colonn " << x << ' ' << y << std::endl;
    ;
    c.disconnect();
    std::cout << "slot disconnected in colonn " << x << ' ' << y << std::endl;
    ;
  }
}

void colonn::doContinMath(const ContinMath::slot_type &slot)
{
  c = continMath.connect(slot);
}

void colonn::haltContinMath()
{
  c.disconnect();
}
