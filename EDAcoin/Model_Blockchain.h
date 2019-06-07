#pragma once

#include "Subject.h"
#include "Model_Block.h"
#include <vector>

class Model_Blockchain: public Subject
{
	public:
		Model_Blockchain();
		~Model_Blockchain();

		//getters
		vector<Model_Block>* get_blockchain(void);
		unsigned int get_cant_boards(void);
		unsigned int get_actual_board(void);

		//setters
		void set_blockchain(vector<Model_Block>* new_blockchain);
		void set_actual_board(unsigned int new_actual_board);

	private:
		vector<Model_Block>* blockchain;

		unsigned int cant_board;
		unsigned int actual_board;
};