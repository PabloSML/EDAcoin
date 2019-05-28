#pragma once

#ifndef IMAGE_DESCRIPTOR_H
#define IMAGE_DESCRIPTOR_H


#include <string>

#include "ImagesManager.h"

#define IMAGE_SIZE_X 180 //256 
#define IMAGE_SIZE_Y 100 //130
#define BUTTON_SIZE_X 80
#define BUTTON_SIZE_Y 80
#define SPACE 10


#define UNIT 1
#define MARGIN_RATE 0.1

#define FLAG_NO_IMAGE_DESCOMPR 0



using namespace std;

class ImageDescriptor
{
public:
	ImageDescriptor();
	ImageDescriptor(const char * path_image);
	ImageDescriptor(const char * path_image, int no_image);
	~ImageDescriptor();

	bool is_select(void);
	void toggle_selection(void);

	void set_pos(int pos_x, int pos_y);

	int get_pos_x(void);
	int get_pos_y(void);

	unsigned int get_width();
	unsigned int get_heigth();

	const char * get_path(void);
	const char * get_name_file(void);
	
	ALLEGRO_BITMAP* get_bitmap(void);

	bool get_error(void);


private:

	bool image_selected;

	const char * path;

	string file_name;

	ALLEGRO_BITMAP* bitmap;

	int pos_x;
	int pos_y;

	bool error;

	unsigned int width;
	unsigned int height;


	string extract_name_file(const char * path_);
};






#endif // !IMAGE_DESCRIPTOR_H

