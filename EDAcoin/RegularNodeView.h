#pragma once
#include "Observer.h"
#include "Node.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class RegularNodeView : public Observer {
public:
	RegularNodeView() { image = nullptr; }
	RegularNodeView(ALLEGRO_BITMAP* newImage);
	RegularNodeView(const char* imgPath);
	~RegularNodeView() { if(image != nullptr) al_destroy_bitmap(image); }

	void setImage(ALLEGRO_BITMAP* newImage);
	void setImage(const char* imgPath);

	virtual void update(void* model);


private:
	ALLEGRO_BITMAP* image;
};