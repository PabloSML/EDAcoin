#pragma once

#include "Subject.h"
#include "Model_Block.h"
#include <vector>
#include "Model_Button_Blockchain.h"


#define BUTTON_LEFT		0
#define BUTTON_RIGHT	1

class Model_Blockchain: public Subject
{
	public:
		Model_Blockchain(ALLEGRO_EVENT_QUEUE* event_queue);
		~Model_Blockchain();

		//getters
		vector<Model_Block*>* get_blockchain(void);
		unsigned int getBlockCount(void);
		unsigned int get_cant_boards(void);
		unsigned int get_actual_board(void);
		bool can_show_merkle_trees(void);
		MerkleNode* getMerkleTree(int index);
		vector<Model_Button_Blockchain*> get_buttons(void);
		ALLEGRO_DISPLAY* getDisplay(void);
		bool shouldEnd(void);
		Model_Block* getBlockbyIndex(unsigned int index);
		

		//setters
		void set_blockchain(vector<Model_Block*>* new_blockchain);
		void set_blockchain(vector<blockHeader>* new_blockHeaders);
		void set_actual_board(unsigned int new_actual_board);
		void set_merkle_trees(vector<MerkleNode*>* new_merkle_trees);

		void triggerEnd(void);

		unsigned int recountBlocks(void);
		bool isInitOk(void);

		void updateBlocksbyIndex(unsigned int index);

	private:
		ALLEGRO_DISPLAY* display;

		bool enable_show_merkle_trees;
		bool end;

		vector<Model_Button_Blockchain*>  model_buttons;

		vector<Model_Block*>* blockchain;
		vector<MerkleNode *> * merkle_tree;

		unsigned int blockCount;
		unsigned int cant_board;
		unsigned int actual_board;

		bool init_ok;


};