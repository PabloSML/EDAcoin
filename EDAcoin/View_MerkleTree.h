#pragma once

#include "Observer.h"
#include "Allegro.h"

#include "allegro5/bitmap.h"

#include "Definitions.h"


class View_MerkleTree : public Observer {

	public:
		View_MerkleTree(ALLEGRO_EVENT_QUEUE* event_queue, unsigned int width_display, unsigned int height_display,
						unsigned int margin_x_display = MERKLE_DISPLAY_MARGIN_DEFAULT_WIDTH,
						unsigned int margin_y_display = MERKLE_DISPLAY_MARGIN_DEFAULT_HEIGTH);
		~View_MerkleTree();

		void update(void * model);

	private:
		
		Allegro graph_resources;

		//**
		ALLEGRO_DISPLAY* display;
		unsigned int width;
		unsigned int height;
		//**

		ALLEGRO_BITMAP * node_image;
		bool init_ok;

};