#include <list>
#include <vector>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <GL/glut.h>
#include <sys/types.h> //typedef unsigned short int uint;
#include <boost/signal.hpp>

#define GL_PI 3.1415926535897932384626433832795028841971693993751

#define CELLSIZE 0.1
#define FISHSIZE 0.05
#define STARTF 2

// == base ==
class base{
	float fi;
	// orientation of animation:
	//  1 - left
	//  2 - right
	//  3 - up
	//  4 - down
	uint dir;
	typedef boost::signal<void ()> OnDejavu;

public:
    bool anime;
	base(){fi=0; dir=1; anime=false; };
	float rotate(float fi_);

	void doOnDejavu(const OnDejavu::slot_type& slot);
	uint setOrient(uint d1);
	//void whereis(float &x, float &z);
	void render(float size, float height, int corners);
private:
    OnDejavu onDejavu;
};
///----
