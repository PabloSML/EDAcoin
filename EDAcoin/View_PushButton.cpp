#include "View_PushButton.h"
#include "allegro5/allegro_color.h"
#include "allegro5/allegro_primitives.h"

#include "Model_PushButton.h"

View_PushButton::
View_PushButton(const char * name_color_toggle1, const char * name_color_toggle2,
				const char * name_color_text, ALLEGRO_FONT * first_font_title) :

	font_title(first_font_title)
{
	this->color_text = al_color_name(name_color_text);
	this->color_toggle1 = al_color_name(name_color_toggle1);
	this->color_toggle2 = al_color_name(name_color_toggle2);

}


View_PushButton::
~View_PushButton(void)
{

}

void View_PushButton::
update(void * model)
{
	Model_PushButton * model_observed = (Model_PushButton *)model;

	ALLEGRO_COLOR actual_color_edit;

	if (model_observed->is_select() == true) //toggle previo = estado 2
	{
		actual_color_edit = this->color_toggle1;
	}
	else
	{										//toggle previo = estado 1
		actual_color_edit = this->color_toggle2;
	}



	float panel_x1 = (float) model_observed->get_pos_x();
	float panel_x2 = panel_x1 + (float)model_observed->get_width();

	float panel_y1 = (float) model_observed->get_pos_y();
	float panel_y2 = panel_y1 + (float) model_observed->get_heigth();

	al_draw_filled_rectangle(panel_x1, panel_y1, panel_x2, panel_y2, actual_color_edit);
	al_draw_text(this->font_title, this->color_text, panel_x1 + (panel_x2 - panel_x1) / 2, panel_y1 +(panel_y2 - panel_y1) / 2,
		ALLEGRO_ALIGN_CENTRE, (model_observed->get_title()).c_str());


}
