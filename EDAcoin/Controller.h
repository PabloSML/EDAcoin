#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <allegro5\allegro.h>
#include "Subject.h"
using namespace std;

struct EventData
{
	ALLEGRO_EVENT * al_ev;
};

class Controller{
public:
	Controller(void) {};
	virtual void parseMouseEvent(EventData * ev) = 0;
	//virtual void parseNetworkEvent(EventData * ev) = 0;
	virtual void parseKeyboardEvent(EventData * ev) = 0;
	virtual void parseTimerEvent(EventData * ev) = 0;

	~Controller() {};
	
};