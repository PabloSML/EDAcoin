#pragma once

#ifndef VIEWER_H
#define VIEWER_H

#include <allegro5\allegro_font.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\allegro_color.h>
#include <allegro5\allegro_primitives.h>

#include "ImagesManager.h"
#include "Board.h"
#include "Definitions.h"




class viewer //Se ocupa de todo lo relacionado con el output de la simulacion
{
public:
	viewer(unsigned int width = WIDTH_DEFAULT, unsigned int height = HEIGHT_DEFAULT, double font_size = FONT_SIZE_DEFAULT );
	~viewer();
	
	bool is_init(void);					 //listo
	void update_display(board & board); //listo
	ALLEGRO_DISPLAY* get_display(void);


private:

	unsigned int height;
	unsigned int width;
	ALLEGRO_DISPLAY * display;
	ALLEGRO_BITMAP* background;
	ALLEGRO_FONT* font;
	double font_size;
	bool is_init_bool;


	ALLEGRO_BITMAP * image_block;
	bool error_image_block; 


	//private methods
	bool init_allegro_elements(const char* path_background, const char* font_path);
	void print_board(board& board); //falta definir
	
};


#endif // !VIEWER_H



