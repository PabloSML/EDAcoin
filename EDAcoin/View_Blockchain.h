#pragma once

#include "Observer.h"


#include "ImageDescriptor.h"
#include "Allegro.h"


class View_Blockchain : public Observer {

	public:
		View_Blockchain(unsigned int width_display, unsigned int heigth_display);
		~View_Blockchain(void);

		void update(void* model);
	
	private:

		
		Allegro graph_resources;
		
		vector<ImageDescriptor> buttons;

		unsigned int margin_x; //margenes
		unsigned int margin_y;


};

