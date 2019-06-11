#pragma once

#include "Observer.h"

#include "allegro5/allegro_font.h"
#include "allegro5/color.h"

class View_BoxText : public Observer
{
public:
	View_BoxText(char const * name_color_panel, char const * name_color_edit_unselect,
		char const * name_color_edit_select, char const * name_color_text,
		ALLEGRO_FONT * first_font_title, ALLEGRO_FONT * first_font_edit_text,
		unsigned int first_width_edit_box, unsigned int first_heigth_edit_box);

	~View_BoxText(void);


	void update(void * model);


	private:

		
		ALLEGRO_FONT * font_title;
		ALLEGRO_FONT * font_edit_text;

		ALLEGRO_COLOR color_text;
		ALLEGRO_COLOR color_panel; 
		ALLEGRO_COLOR color_edit_unselect;
		ALLEGRO_COLOR color_edit_select;

		unsigned int width_edit_box;
		unsigned int heigth_edit_box;

};