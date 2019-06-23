#pragma once

#include "MerkleNode.h"
#include "Subject.h"
#include "Allegro.h"
#include <vector>


class Model_MerkleTree : public Subject
{
	public:
		Model_MerkleTree(MerkleNode* new_merkle_root, ALLEGRO_EVENT_QUEUE* event_queue, const string& blockID);
		~Model_MerkleTree();

		//getters
		MerkleNode * get_merkle_root(void);
		ALLEGRO_DISPLAY* getDisplay(void);
		bool shouldEnd(void);

		//setters
		void set_merkle_root(MerkleNode * new_merkle_root);
		void triggerEnd(void);
		bool isInitOk(void);


	private:
		MerkleNode * merkle_root;
		ALLEGRO_DISPLAY* display;
		bool end;

		bool init_ok;
};