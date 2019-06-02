#pragma once
#include "Observer.h"
#include "Node.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class RegularNodeView : public Observer {
public:
	RegularNodeView() { image = nullptr; }
	RegularNodeView(ALLEGRO_BITMAP* newImage, unsigned int newPosx, unsigned int newPosy);
	RegularNodeView(const char* imgPath, unsigned int newPosx, unsigned int newPosy);
	~RegularNodeView() { al_destroy_bitmap(image); }

	void setImage(ALLEGRO_BITMAP* newImage);
	void setImage(const char* imgPath);
	void setPos(unsigned int newPosx, unsigned int newPosy);

	virtual void update(void* model);

private:
	ALLEGRO_BITMAP* image;
	unsigned int posX;
	unsigned int posY;
};