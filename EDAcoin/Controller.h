#pragma once
#include <iostream>
#include <fstream>
#include <allegro5\allegro.h>
#include "Subject.h"

using namespace std;

struct EventData
{
	ALLEGRO_EVENT * al_ev;
	ALLEGRO_EVENT_QUEUE* event_queue;
};

class Controller{
public:
	Controller(Subject* owner) : subject_attach(owner) {}
	virtual void parseMouseEvent(EventData * ev) = 0;
	virtual void parseNetworkEvent(void) = 0;
	virtual void parseKeyboardEvent(EventData * ev) = 0;
	virtual void parseTimerEvent(EventData * ev) = 0;

	virtual void forwardMouseEvent(EventData* ev) = 0;
	virtual void forwardKeyboardEvent(EventData* ev) = 0;

	void attach_subject(Subject * subject_to_attach);
	void dettach_subject(void);

	Subject* get_subject_attach(void);
	bool is_subject_attached(void);

	~Controller();

private:
	Subject* subject_attach;
	
};