#pragma once

#include <iostream>
#include <fstream>

#include "Model_Block.h"
#include <vector>
#include "Board.h"
#include "Viewer.h"
#include "MerkleNode.h"
#include "Supervisor.h"

class General_Controller
{

	public:
	General_Controller(void);
	~General_Controller();
	void dispatcher(void);
	bool is_finish(void);

	void update(vector<Block> * blockChain, vector<MerkleNode *> merkle_trees);
	viewer& get_viewer(void);
	void  set_supervisor(supervisor & superv);

	private:

		viewer			general_viewer;
		board			general_board;
		supervisor *	general_supervisor;

		vector<ImageDescriptor> buttons;


		bool all_ok;

};