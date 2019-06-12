#include "Widget.h"
#include "Definitions.h"

Widget::Widget(unsigned int first_width, unsigned int first_heigth, unsigned int first_pos_x, unsigned int first_pos_y):
	width(first_width), height(first_heigth), pos_x(first_pos_x), pos_y(first_pos_y)
{


}

//listo
Widget::~Widget()
{

}



//listo
void Widget::set_pos(int pos_x, int pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

//listo
int Widget::get_pos_x(void)
{
	return (this->pos_x);
}

//listo
int Widget::get_pos_y(void)
{
	return (this->pos_y);
}

//listo
unsigned int Widget::get_width()
{
	return (this->width);
}

//listo
unsigned int Widget::get_heigth()
{
	return (this->height);
}



void Widget::
set_width(unsigned int new_width) { this->width = new_width; }


void Widget::
set_heigth(unsigned int new_heigth) { this->height = new_heigth; }

