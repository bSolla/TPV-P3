#include "ArkanoidObject.h"


ArkanoidObject::ArkanoidObject(){
}


ArkanoidObject::~ArkanoidObject(){
}

void ArkanoidObject::saveToFile(ofstream &file) {
	file << position.getX() << " " << position.getY() << " ";
}

void ArkanoidObject::loadFromFile(ifstream &file) {
	double x, y;

	file >> x >> y;
	position.setX(x);
	position.setY(y);
}
