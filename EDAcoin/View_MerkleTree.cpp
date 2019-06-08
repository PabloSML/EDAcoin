#include "View_MerkleTree.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"

#include "Model_MerkleTree.h"
#include "ImagesManager.h"

//auxiliar functions
static void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
	unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font, ALLEGRO_BITMAP* nodeImge);

static unsigned int get_depth_tree(MerkleNode * merkle_root);


View_MerkleTree::
View_MerkleTree(unsigned int width_display, unsigned int heigth_display, unsigned int margin_x, unsigned int margin_y) :
	graph_resources(width_display + 2*margin_x, heigth_display + 2*margin_y)
{
	this->node_image = al_load_bitmap(MERKLE_NODE_IMAGE_PATH);

	if (this->node_image == nullptr)
	{
		this->init_ok = false;
	}
	else {
		this->init_ok = true;
	}

}

View_MerkleTree::
~View_MerkleTree(void)
{

	if (this->init_ok == true)
	{
		al_destroy_bitmap(this->node_image);
		this->init_ok = false;
	}

}

void View_MerkleTree::
update(void * model) {

	Model_MerkleTree * model_observed = (Model_MerkleTree *) model;

	MerkleNode * merkle_root = model_observed->get_merkle_root();
	unsigned int width = (this->graph_resources).GetDisplayW();
	unsigned int height = (this->graph_resources).GetDisplayH();

	unsigned int depth_tree = get_depth_tree(merkle_root);
	unsigned int level = 1;
	unsigned int root_pos_y = 0;
	unsigned int root_pos_x = width/2;

	ALLEGRO_FONT* font_nodes = al_load_ttf_font(NODE_FONT_PATH, NODE_FONT_SIZE*(1 + (SCALE_LEVEL_SIZE_TEXT_NODE - 1) / depth_tree), 0);

	draw_nodes(merkle_root, root_pos_x, root_pos_y, depth_tree, level, width, height, font_nodes, this->node_image);

}

ALLEGRO_DISPLAY*
View_MerkleTree::getDisplay(void)
{
	return graph_resources.getDisplay();
}

static void draw_nodes(MerkleNode * merkleRoot, unsigned int last_pos_x, unsigned int last_pos_y,
	unsigned int depth, unsigned int level, unsigned int width, unsigned int height, ALLEGRO_FONT * font, ALLEGRO_BITMAP* nodeImg)
{

	if (!(merkleRoot->getLeft() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x - width / pow(2, level + 1);
		unsigned int child_pos_y = (level)*(height / depth);

		al_draw_line((float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			(float)(child_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(child_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			LINE_COLOR, LINE_THICKNESS);


		draw_nodes(merkleRoot->getLeft(), child_pos_x, child_pos_y, depth, level + 1, width, height, font, nodeImg);
	}

	if (!(merkleRoot->getRight() == nullptr))
	{
		unsigned int child_pos_x = last_pos_x + width / pow(2, level + 1);
		unsigned int child_pos_y = (level)*(height / depth);

		al_draw_line((float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			(float)(child_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(child_pos_y + MARGIN_Y_DISPLAY * (UNIT)),
			LINE_COLOR, LINE_THICKNESS);

		draw_nodes(merkleRoot->getRight(), child_pos_x, child_pos_y, depth, level + 1, width, height, font, nodeImg);
	}

	/*al_draw_scaled_bitmap(nodeImg, 0, 0, al_get_bitmap_width(nodeImg), al_get_bitmap_height(nodeImg), (last_pos_x + MARGIN_X_DISPLAY * (UNIT)) - NODE_RADIUS * (1 + SCALE_LEVEL_SIZE_NODE / level),
		last_pos_y + MARGIN_Y_DISPLAY * (UNIT) - NODE_RADIUS * (1 + SCALE_LEVEL_SIZE_NODE / level), NODE_RADIUS*(1 + SCALE_LEVEL_SIZE_NODE / level)*2, NODE_RADIUS*(1 + SCALE_LEVEL_SIZE_NODE / level) * 2, 0);  Imagen para el nodo (graciosa)*/

	al_draw_filled_circle(last_pos_x + MARGIN_X_DISPLAY * (UNIT), last_pos_y + MARGIN_Y_DISPLAY * (UNIT), NODE_RADIUS*(1 + SCALE_LEVEL_SIZE_NODE / level), NODE_COLOR);

	if (merkleRoot->isLeaf())
	{
		al_draw_text(font, MESSAGE_NODE_COLOR, (float)(last_pos_x + MARGIN_X_DISPLAY * (UNIT)), (float)(last_pos_y + MARGIN_Y_DISPLAY * (UNIT)-(1 + 1 / depth) *DX_TEXT),
			ALLEGRO_ALIGN_CENTER, (merkleRoot->getNodeID()).c_str());

	}
}

static unsigned int get_depth_tree(MerkleNode * merkle_root)
{
	if (merkle_root->isLeaf())
	{
		return 0;
	}
	else
	{
		return (1 + get_depth_tree(merkle_root->getLeft()));
	}
}
