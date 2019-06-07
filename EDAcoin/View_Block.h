#pragma once

#include "Observer.h"


#include "allegro5/bitmap.h"
#include "allegro5/allegro_font.h"

class View_Block : public Observer {

	public:
		View_Block();
		~View_Block();

		void update(void * model);
		bool init_was_ok(void);

	private:

		ALLEGRO_BITMAP * bitmap;
		ALLEGRO_FONT * font;
		bool init_ok;

};