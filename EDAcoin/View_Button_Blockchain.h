#pragma once
#include "Observer.h"

#include "allegro5/allegro_font.h"
#include "allegro5/color.h"

class View_Button_Blockchain : public Observer
{
public:
	View_Button_Blockchain(const char * path_image);
	View_Button_Blockchain() {};
	~View_Button_Blockchain(void);


	bool fail(void);

	void update(void * model);

private:

	ALLEGRO_BITMAP * image_represent;
	bool init;

};