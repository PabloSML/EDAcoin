#pragma once
#include <iostream>
#include <fstream>
#include <allegro5\allegro.h>
#include "Subject.h"

using namespace std;

struct EventData
{
	ALLEGRO_EVENT * al_ev;
};

class Controller{
public:
	Controller(Subject* creator) : subject_attach(creator) {}
	virtual void parseMouseEvent(EventData * ev) = 0;
	//virtual void parseNetworkEvent(EventData * ev) = 0;
	virtual void parseKeyboardEvent(EventData * ev) = 0;
	virtual void parseTimerEvent(EventData * ev) = 0;


	void attach_subject(Subject * subject_to_attach);
	void dettach_subject(void);

	Subject* get_subject_attach(void);
	bool is_subject_attached(void);

	~Controller();

private:
	Subject* subject_attach;
	
};