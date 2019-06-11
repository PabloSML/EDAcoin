#pragma once
#include "Observer.h"

#include "allegro5/allegro_font.h"
#include "allegro5/color.h"

class View_PushButton : public Observer
{
public:
	View_PushButton(const char  * name_color_toggle1, const char  * name_color_toggle2,
		const char  * name_color_text, ALLEGRO_FONT * first_font_title);
	View_PushButton() {};
	~View_PushButton(void);


	void update(void * model);

private:

	ALLEGRO_FONT * font_title;

	ALLEGRO_COLOR color_text;
	ALLEGRO_COLOR color_toggle1;
	ALLEGRO_COLOR color_toggle2;

};