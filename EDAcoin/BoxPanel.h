#pragma once


#include "Subject.h"
#include <stdio.h>	

using namespace std;


class BoxPanel : public Subject
{
public:

	BoxPanel(string& first_title, unsigned int first_width, unsigned int first_heigth);
	~BoxPanel();

	//getters
	string	get_title(void);
	unsigned int get_pos_x(void);
	unsigned int get_pos_y(void);
	unsigned int get_width(void);
	unsigned int get_heigth(void);
	bool is_select(void);

	//setters
	void set_pos_x(unsigned int new_pos_x);
	void set_pos_y(unsigned int new_pos_y);
	void set_width(unsigned int new_width);
	void set_heigth(unsigned int new_heigth);


private:
	string title;
	unsigned int pos_x;
	unsigned int pos_y;
	unsigned int width;
	unsigned int heigth;
	bool is_selected;
};