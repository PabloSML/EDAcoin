#pragma once


class Widget
{
	public:
		Widget(unsigned int first_width, unsigned int first_heigth, unsigned int first_pos_x, unsigned int first_pos_y);
		~Widget();

		void set_pos(int pos_x, int pos_y);
		void set_heigth(unsigned int new_heigth);
		void set_width(unsigned int new_width);


		int get_pos_x(void);
		int get_pos_y(void);

		unsigned int get_width();
		unsigned int get_heigth();


	private:

		int pos_x;
		int pos_y;

		unsigned int width;
		unsigned int height;
};
