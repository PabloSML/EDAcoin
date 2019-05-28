#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include "allegro5/allegro.h"
#include "allegro5/color.h"

#define WIDTH_DEFAULT			1000
#define HEIGHT_DEFAULT			600
#define FONT_SIZE_DEFAULT		30

#define BACKGROUND_PATH			"background2.png" //Imagen de fondo

#define FONT_PATH				"Font.ttf"
#define FONT_COLOR				"red"

#define IMAGE_BLOCK_PATH		"block-image.png"

#define PATH_BUTTON_LEFT		"button_left2.png"
#define PATH_BUTTON_RIGHT		"button_right2.png"

#define NODE_RADIUS				40
#define NODE_COLOR				(al_map_rgb(0,0,204)) // verde oscuro

#define LINE_COLOR				(al_map_rgb(102,204,255)) // azul claro
#define LINE_THICKNESS			10

#define MESSAGE_NODE_COLOR		(al_map_rgb(255,0,0)) // rojo puro
#define NODE_FONT_PATH			"Font.ttf"
#define NODE_FONT_COLOR			"red"
#define NODE_FONT_SIZE			8

#endif // !DEFINITIONS_H
