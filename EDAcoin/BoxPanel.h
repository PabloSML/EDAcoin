#pragma once


#include "Subject.h"
#include <stdio.h>	
#include "Widget.h"

using namespace std;


class BoxPanel : public Subject, public Widget
{
public:

	BoxPanel(string& first_title, unsigned int first_width, unsigned int first_heigth);
	~BoxPanel();

	//getters
	string	get_title(void);
	bool is_select(void);
	
	//**
	void toggleSelect(void);
	//**

private:
	string title;
	bool is_selected;
};