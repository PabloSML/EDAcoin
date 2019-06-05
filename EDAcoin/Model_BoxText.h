#pragma once

#include "BoxPanel.h"
#include <stdio.h>	

using namespace std;


class Model_BoxText : public BoxPanel
{
	public:
		
		Model_BoxText(string& first_title, unsigned int first_width, unsigned int first_heigth);
		~Model_BoxText();

		//getters
		string	get_actual_text(void);
		

		//setters
		void set_text(string& new_text);



	private:
		string buffer_edit_text;

};