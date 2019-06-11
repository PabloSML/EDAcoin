#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h> //manejo de fonts
#include <allegro5/allegro_ttf.h> //Manejo de ttfs

#define DISPLAY_H	1700
#define DISPLAY_W	1300
#define TEXTFONT "allegrofiles\\textfont.ttf"
#define TEXTSIZE 30
#define FPS	1



enum align {center, right, left};



ALLEGRO_EVENT_QUEUE* initAllegro(ALLEGRO_TIMER*& timer);
void destroyAllegro(ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_TIMER*& timer);

class Allegro
{
public:
	//constructores
	Allegro();
	~Allegro();

	//metodos especiales
	void setDisplayColor(unsigned char r, unsigned char g, unsigned char b);
	void updateDisplay(void);
	//enum al_event getNextEvent(void);
	//ALLEGRO_EVENT getNextEvent(void);
	void printText(const char* text, int x,int y,enum align al, ALLEGRO_FONT * al_font = NULL);

	void drawImage(ALLEGRO_BITMAP* image, int x, int y, int width = 0, int height = 0);

private:
	ALLEGRO_FONT* font;
};