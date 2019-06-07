#pragma once

#include "Observer.h"
#include "Allegro.h"
#include "Model_MerkleTree.h"
#include "allegro5/bitmap.h"

#include "Definitions.h"


class View_MerkleTree : public Observer {

	public:
		View_MerkleTree(unsigned int width_display, unsigned int height_display,
						unsigned int margin_x_display = MERKLE_DISPLAY_MARGIN_DEFAULT_WIDTH,
						unsigned int margin_y_display = MERKLE_DISPLAY_MARGIN_DEFAULT_HEIGTH);
		~View_MerkleTree();

		void update(void * model);

	private:
		Model_MerkleTree * model_observed;
		Allegro graph_resources;

		ALLEGRO_BITMAP * node_image;
		bool init_ok;

};