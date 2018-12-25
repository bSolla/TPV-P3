#pragma once
#include "ArkanoidObject.h"
#include <fstream>

class MovingObject : public ArkanoidObject {
protected:
	Vector2D speed;
public:
	MovingObject();
	virtual ~MovingObject();

	virtual void update();
	virtual void loadFromFile(ifstream &file); 
	virtual void saveToFile(ofstream &file); 

};

