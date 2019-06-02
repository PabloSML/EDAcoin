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
RegularNodeView::update(void* model)
{
	Node* nodeModel = (Node*)model;

}