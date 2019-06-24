#pragma once

#include "Subject.h"

#include "Model_PushButton.h"
#include "Model_BoxText.h"

#include <vector>
#include <string>

using namespace std;

class Model_Transaction_GUI: public Subject
{
	public:
		Model_Transaction_GUI(unsigned int cant_boxtexts, unsigned int cant_pushbuttons,
							  const char* titles_boxtexts [], const char * titles_pushbuttons[],
							  unsigned int width_boxtexts, unsigned int height_boxtetxs,
							  unsigned int width_pushbuttons, unsigned int height_pushbuttons,
							  unsigned int pos_x, unsigned int pos_y, unsigned int margin_btw_buttons);
		~Model_Transaction_GUI();

		string get_text(unsigned int which_boxtext);

		unsigned int get_pos_x(void);
		unsigned int get_pos_y(void);
		unsigned int get_size_x(void);
		unsigned int get_size_y(void);


		unsigned int get_cant_pushbuttons(void);
		unsigned int get_cant_boxttexts(void);

		Model_PushButton* get_pushbutton(unsigned int which_pushbutton);
		Model_BoxText*	  get_boxtext	(unsigned int which_boxttext);

		void receive_transaction(void);
		void attend_transaction(void);

		bool is_transaction_waiting(void);

	private:
		vector<Model_PushButton*> * pushbuttons;
		vector<Model_BoxText*> * boxtexts;

		unsigned int cant_boxtexts;
		unsigned int cant_pushbuttons;

		unsigned int pos_x;
		unsigned int pos_y;

		unsigned int margin_btw_buttons;


		bool transaction_waiting;


		bool init_ok;

};