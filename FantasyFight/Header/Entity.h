#ifndef _Classes_Entity__
#define  _Classes_Entity_

#include <string>

using namespace std;

class Entity 
{
private:
	int id;
	string name;
public:
	Entity ( string name );
	~Entity ();
};



#endif