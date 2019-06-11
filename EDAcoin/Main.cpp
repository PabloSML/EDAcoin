#include "Model_PushButton.h"
#include "View_PushButton.h"
#include "Controller_PushButton.h"

#include "Model_BoxText.h"
#include "View_BoxText.h"
#include "Controller_BoxText.h"

#include "Allegro.h"
#include <iostream>

#include "Controller.h"

#define COLOR_RED	"red"
#define COLOR_BLUE	"blue"
#define COLOR_WHITE "white"

#include "allegro5/color.h"
#include "allegro5/allegro_color.h"

int main()

{
	ALLEGRO_EVENT_QUEUE* queue = initAllegro();
	ALLEGRO_DISPLAY * display = al_create_display(900, 600);
	al_clear_to_color(al_color_name("white"));
	al_register_event_source(queue, al_get_display_event_source(display));

	ALLEGRO_FONT * font = al_load_font("American Captain.ttf", 20, 0);

	string title("BOTON PRUEBA");

	Model_PushButton button = Model_PushButton(title, 100, 100);
	button.set_pos_x(300);
	button.set_pos_y(400);



	string title2("TEXTO AQUI");

	Model_BoxText text_box = Model_BoxText(title2, 200, 200);
	text_box.set_pos_x(100);
	text_box.set_pos_y(100);



	View_PushButton v_button("red", "blue", "white", font);

	button.attach(&v_button);


	View_BoxText v_text_box("red", "blue", "green", "black", font, font, 100, 80);

	text_box.attach(&v_text_box);


	Controller_PushButton c_button = Controller_PushButton((Subject *)&button);


	Controller_BoxText c_box_text = Controller_BoxText((Subject*)&text_box);


	ALLEGRO_EVENT event;

	al_get_next_event(queue, &event);


	EventData evento;

	bool close = false;

	while (close == false)
	{
		al_wait_for_event(queue, &event);
		evento.al_ev = &event;

		switch (event.type)
		{
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			close = true;
			break;
		case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
			c_button.parseMouseEvent(&evento);
			c_box_text.parseMouseEvent(&evento);
			al_flip_display();
			break;
		case ALLEGRO_EVENT_KEY_DOWN:
			c_button.parseKeyboardEvent(&evento);
			c_box_text.parseKeyboardEvent(&evento);
			al_flip_display();
			break;
		};
	}

	al_destroy_display(display);

}



