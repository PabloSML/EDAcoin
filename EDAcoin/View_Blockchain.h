#pragma once

#include "Observer.h"


#include "ImageDescriptor.h"
#include "Allegro.h"
#include <vector>


class View_Blockchain : public Observer {

	public:
		View_Blockchain(ALLEGRO_EVENT_QUEUE* event_queue, unsigned int width_display, unsigned int heigth_display);
		~View_Blockchain(void);

		void update(void* model);
	
	private:

		Allegro graph_resources;
		vector <ImageDescriptor> buttons;

		//**
		ALLEGRO_DISPLAY* display;
		unsigned int width;
		unsigned int height;
		//**

		unsigned int margin_x; //margenes
		unsigned int margin_y;

		bool init_ok;
};

