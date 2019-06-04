#include "RegularNodeView.h"
#include <iostream>

RegularNodeView::RegularNodeView(ALLEGRO_BITMAP* newImage, float newPosx, float newPosy)
{
	image = newImage;
	posX = newPosx;
	posY = newPosy;
}

RegularNodeView::RegularNodeView(const char* imgPath, float newPosx, float newPosy)
{
	image = al_load_bitmap(imgPath);
	if (!image)
		std::cout << "RNV bitmap incorrect load" << std::endl;
	posX = newPosx;
	posY = newPosy;
}

void
RegularNodeView::setPos(float newPosx, float newPosy)
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
	nodeID = nodeModel->getNodeID();
	nodeType = nodeModel->getNodeType();
}

void
RegularNodeView::draw(void)
{
	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), posX, posY, 150, 150, 0);
}