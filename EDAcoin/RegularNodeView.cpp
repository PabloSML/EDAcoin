#include "RegularNodeView.h"
#include <iostream>

RegularNodeView::RegularNodeView(ALLEGRO_BITMAP* newImage, unsigned int newPosx, unsigned int newPosy)
{
	image = newImage;
	posX = newPosx;
	posY = newPosy;
}

RegularNodeView::RegularNodeView(const char* imgPath, unsigned int newPosx, unsigned int newPosy)
{
	image = al_load_bitmap(imgPath);
	if (!image)
		std::cout << "RNV bitmap incorrect load" << std::endl;
	posX = newPosx;
	posY = newPosy;
}

void
RegularNodeView::setPos(unsigned int newPosx, unsigned int newPosy)
{
	posX = newPosx;
	posY = newPosy;
}

void
RegularNodeView::setImage(ALLEGRO_BITMAP* newImage)
{
	if (image != nullptr)
		al_destroy_bitmap(image);
	image = newImage;
}

void
RegularNodeView::setImage(const char* imgPath)
{
	if (image != nullptr)
		al_destroy_bitmap(image);
	image = al_load_bitmap(imgPath);
	if (!image)
		std::cout << "RNV bitmap incorrect load" << std::endl;
}

void
RegularNodeView::update(void* model)
{
	Node* nodeModel = (Node*)model;

}