#include "View_BoxText.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"

#include "Model_BoxText.h"

#include "Definitions.h"

#define MARGIN_Y_TITLE 5
#define PERCENT_POSITION_Y_EDIT_TEXT 0.6

View_BoxText::
View_BoxText(	char const * name_color_panel, char const * name_color_edit_unselect,
				char const * name_color_edit_select, char const * name_color_text,
				char const * first_font_title, char const * first_font_edit_text,
				unsigned int first_width_edit_box, 	unsigned int first_heigth_edit_box) :

	width_edit_box(first_width_edit_box), heigth_edit_box(first_heigth_edit_box),
	init_ok(false)
{

	this->font_edit_text = al_load_font(first_font_edit_text, SIZE_FONT_EDIT_TEXT, 0);

	if (this->font_edit_text != nullptr)
	{
		this->font_title = al_load_font(first_font_title, SIZE_FONT_TITLE_EDIT, 0);

		if (this->font_title != nullptr)
		{
			this->color_text = al_color_name(name_color_text);
			this->color_panel = al_color_name(name_color_panel);
			this->color_edit_select = al_color_name(name_color_edit_select);
			this->color_edit_unselect = al_color_name(name_color_edit_unselect);

			this->init_ok = true;
		}
		else
		{
			al_destroy_font(this->font_edit_text);
		}
	}

	

	

}


View_BoxText::
~View_BoxText(void)
{
	if (this->init_ok == true)
	{
		al_destroy_font(this->font_edit_text);
		al_destroy_font(this->font_title);
		this->init_ok = false;
	}

}

void View_BoxText::
update(void * model)
{
	Model_BoxText * model_observed = (Model_BoxText *) model;

	float panel_x1 = (float) model_observed->get_pos_x();
	float panel_x2 = panel_x1 + (float)model_observed->get_width();

	float panel_y1 = (float)model_observed->get_pos_y();
	float panel_y2 = panel_y1 + (float)model_observed->get_heigth();


	al_draw_filled_rectangle(panel_x1, panel_y1, panel_x2, panel_y2, this->color_panel);
	al_draw_text(this->font_title, this->color_text, panel_x1 + (panel_x2 - panel_x1) / 2, panel_y1 + MARGIN_Y_TITLE,
			     ALLEGRO_ALIGN_CENTRE, (model_observed->get_title()).c_str());




	float edit_aux_x = panel_x1 + (panel_x2 - panel_x1) / 2;
	float edit_aux_y = panel_y1 + PERCENT_POSITION_Y_EDIT_TEXT * model_observed->get_heigth();

	float edit_x1 = edit_aux_x - (float)((this->width_edit_box) / 2);
	float edit_x2 = edit_aux_x + (float)((this->width_edit_box) / 2);

	float edit_y1 = edit_aux_y - (float)((this->heigth_edit_box) / 2);
	float edit_y2 = edit_aux_y + (float)((this->heigth_edit_box) / 2);

	ALLEGRO_COLOR actual_color_edit;

	if (model_observed->is_select() == true)
	{
		actual_color_edit = this->color_edit_select;
	}
	else
	{
		actual_color_edit = this->color_edit_unselect;
	}

	al_draw_filled_rectangle(edit_x1, edit_y1, edit_x2, edit_y2, actual_color_edit);
	al_draw_text(this->font_edit_text, this->color_text, edit_aux_x, edit_aux_y,
		ALLEGRO_ALIGN_CENTRE, (model_observed->get_actual_text()).c_str());

}
