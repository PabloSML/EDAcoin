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
	string merkleRoot;
}blockHeader;



class Model_Block : public Subject {
public:
	Model_Block(string& blockID, string& merkleRoot, unsigned int& txsCount, vector<TransactionS>& transactions);
	Model_Block();
	~Model_Block();

	string getBlockID(void) const;
	string getMerkleRoot(void) const;
	unsigned int getTxsCount(void) const;
	vector<TransactionS> get_transactions(void) const;
	string get_previous_blockID(void);
	void addTransaction(TransactionS& newTx);
	bool hasTransactions(void);
	blockHeader getBlockHeader(void) const; // crea una estructura blockHeader y la devuelve en su nombre
	unsigned long get_index_in_blockchain(void);


	unsigned int get_pos_x(void);
	unsigned int get_pos_y(void);
	unsigned int get_size_x(void);
	unsigned int get_size_y(void);
	

	void set_pos_x(unsigned int new_pos_x);
	void set_pos_y(unsigned int new_pos_y);
	void set_size_x(unsigned int new_size_x);
	void set_size_y(unsigned int new_size_y);

	//**Le agregue el event_queue para que el constructor de la view pueda registrar el display creado.
	void createMerkleTreeModel(MerkleNode* root, ALLEGRO_EVENT_QUEUE* event_queue);
	void destroyMerkleTreeModel(void);
	Model_MerkleTree* getMerkleTreeModel(void);
	void setMerkleTreeModel(Model_MerkleTree* m);

	void set_merkle_root(string& new_merkle_root);
	void set_previous_blockID(string& new_prev_blockID);
	void set_index_block_in_bchn(unsigned long new_index);
	
	bool operator==(Model_Block compare_block);

private:

	string blockID;
	string prev_blockID;
	string merkleRoot;
	unsigned int txsCount;
	vector<TransactionS> transactions;
	unsigned long nounce;

	unsigned int pos_x;
	unsigned int pos_y;


	unsigned int width_image;
	unsigned int heigth_image;

	Model_MerkleTree* myMerkleTreeModel;

	unsigned long index_block;

};