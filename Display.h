#pragma once
#include<iostream>
#include"Utilities.h"
using namespace std;
class Display
{
public:
	Display();
	~Display();
	void start();
private:
	Utilities util = Utilities();
	Utilities* utilities=&util;
};