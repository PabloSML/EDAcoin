#include "Model_MerkleTree.h"
#include "Definitions.h"


Model_MerkleTree::
Model_MerkleTree(MerkleNode* new_merkle_root, ALLEGRO_EVENT_QUEUE* event_queue, const string& blockID) : merkle_root(new_merkle_root), end(false)
{
	//**
	display = al_create_display(WIDTH_DEFAULT + 2 * MARGIN_X_DISPLAY, HEIGHT_DEFAULT + 2 * MARGIN_Y_DISPLAY); // Intenta crear display de fallar devuelve NULL
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		init_ok = false;
		return;
	}
	init_ok = true;
	al_clear_to_color(al_map_rgb(255, 255, 255)); //Hace clear del backbuffer del diplay al color RGB 0,0,0 (negro)
	al_register_event_source(event_queue, al_get_display_event_source(display)); //REGISTRAMOS EL DISPLAY
	al_set_window_title(display, (blockID + "'s Merkle Tree View").c_str());
	//**
}

Model_MerkleTree::~Model_MerkleTree() {
	if (this->init_ok == true)
	{
		al_destroy_display(display);
		this->init_ok = false;
	}
}

//getters
MerkleNode * Model_MerkleTree::get_merkle_root(void) { return this->merkle_root; }
ALLEGRO_DISPLAY* Model_MerkleTree::getDisplay(void) { return display; }
bool Model_MerkleTree::shouldEnd(void) { return end; }

//setters
void Model_MerkleTree::
set_merkle_root(MerkleNode * new_merkle_root) { this->merkle_root = new_merkle_root; }
void Model_MerkleTree::triggerEnd(void) { end = true; }
bool Model_MerkleTree::isInitOk(void) { return init_ok; }
