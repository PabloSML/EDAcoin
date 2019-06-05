#pragma once
#include "Observer.h"
#include "Model_PushButton.h"
#include "allegro5/allegro_font.h"
#include "allegro5/color.h"

class View_PushButton : public Observer
{
	View_PushButton(char const * name_color_toggle1, char const * name_color_toggle2,
		char const * name_color_text, ALLEGRO_FONT * first_font_title)

	~View_PushButton(void);


	void update(void * model);

private:

	Model_PushButton * model_observed;

	ALLEGRO_FONT * font_title;

	ALLEGRO_COLOR color_text;
	ALLEGRO_COLOR color_toggle1;
	ALLEGRO_COLOR color_toggle2;

};