#include "RegularNodeView.h"
#include <iostream>
#include <allegro5\allegro_color.h>

RegularNodeView::RegularNodeView(ALLEGRO_BITMAP* newImage)
{
	image = newImage;
}

RegularNodeView::RegularNodeView(const char* imgPath)
{
	image = al_load_bitmap(imgPath);
	if (!image)
		std::cout << "RNV bitmap incorrect load" << std::endl;
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
	pos_t nodePos = nodeModel->getPos();

	al_draw_scaled_bitmap(image, 0, 0, al_get_bitmap_width(image), al_get_bitmap_height(image), nodePos.posX, nodePos.posY, NODE_IMG_SIZE, NODE_IMG_SIZE, 0);
	double amount = nodeModel->get_amount_wallet();
	//ALLEGRO_FONT * font =al_load_ttf_font(TEXTFONT, 20, 0);
	//al_draw_textf(font, al_color_name("red"), nodePos.posX + RADIUS, nodePos.posY + RADIUS/2, ALLEGRO_ALIGN_CENTER, "%.2f", amount);
	//string str = nodeModel->getNodeID();
	//const char* nodeID = (nodeModel->getNodeID()).c_str();
	//al_draw_text(font, al_color_name("red"), nodePos.posX , nodePos.posY + NODE_IMG_SIZE/2, ALLEGRO_ALIGN_LEFT, (nodeModel->getNodeID()).c_str());
}
