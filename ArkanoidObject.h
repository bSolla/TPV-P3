#pragma once
#include "SDLGameObject.h"
class ArkanoidObject :
	public SDLGameObject
{
public:
	ArkanoidObject();
	~ArkanoidObject();

	virtual void loadFromFile(ifstream &file);

	virtual void saveToFile(ofstream &file);
};

