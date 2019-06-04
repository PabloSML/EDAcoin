#pragma once
#include "Observer.h"
#include "Node.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

class RegularNodeView : public Observer {
public:
	RegularNodeView() { image = nullptr; }
	RegularNodeView(ALLEGRO_BITMAP* newImage, float newPosx, float newPosy);
	RegularNodeView(const char* imgPath, float newPosx, float newPosy);
	~RegularNodeView() { if(image != nullptr) al_destroy_bitmap(image); }

	void setImage(ALLEGRO_BITMAP* newImage);
	void setImage(const char* imgPath);
	void setPos(float newPosx, float newPosy);

	virtual void update(void* model);

private:
	ALLEGRO_BITMAP* image;
	float posX;
	float posY;

	// subject data
	string nodeID;
	string nodeType;
};