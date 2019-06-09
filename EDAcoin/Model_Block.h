#pragma once

#include <string>
#include <vector>
#include "Definitions.h"
#include "Subject.h"
#include "Model_MerkleTree.h"
#include "View_MerkleTree.h"


using namespace std;

typedef struct {		// estructura de blockHeader por si sirve
	string blockID;
	unsigned long merkleRoot;
}blockHeader;



class Model_Block : public Subject {
public:
	Model_Block(string& blockID, unsigned long& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions);
	Model_Block();
	~Model_Block();

	string getBlockID(void) const;
	unsigned long getMerkleRoot(void) const;
	unsigned int getTxsCount(void) const;
	vector<TransactionS> get_transactions(void) const;
	blockHeader getBlockHeader(void) const; // crea una estructura blockHeader y la devuelve en su nombre

	ALLEGRO_DISPLAY* getEnviroment(void);
	unsigned int get_pos_x(void);
	unsigned int get_pos_y(void);
	unsigned int get_size_x(void);
	unsigned int get_size_y(void);

	void setEnviroment(ALLEGRO_DISPLAY* newEnviroment);
	void set_pos_x(unsigned int new_pos_x);
	void set_pos_y(unsigned int new_pos_y);
	void set_size_x(unsigned int new_size_x);
	void set_size_y(unsigned int new_size_y);

	void createMerkleTreeModel(MerkleNode* root);
	void destroyMerkleTreeModel(void);

private:
	
	string blockID;
	unsigned long merkleRoot;
	unsigned int txsCount;
	vector<TransactionS> transactions;

	unsigned int pos_x;
	unsigned int pos_y;

	unsigned int width_image;
	unsigned int heigth_image;

	Model_MerkleTree* myMerkleTreeModel;

	ALLEGRO_DISPLAY* enviroment;

};