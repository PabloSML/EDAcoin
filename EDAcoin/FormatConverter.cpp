#include "FormatConverter.h"
#include <iostream>
#include <stdint.h>
#include "Labels.h"

using namespace std;

json Transactions2Json(TransactionS& t)
{
	json j;
	j[LABEL_TXS_TXID] = t.txID;
	//**
	j[LABEL_TXS_PUBKEY] =t.PubKey;
	j[LABEL_TXS_SIGNATURE] = ByteVector2String(t.signature);
	//**
	int count = 0;
	for (InputS i : t.inputs)
	{
		j[LABEL_TXS_INPUT][count][LABEL_BLOCK_BLOCK_ID] = i.blockID;
		j[LABEL_TXS_INPUT][count][LABEL_TXS_TXID] = i.txID;
		count++;
	}
	count = 0;
	for (OutputS i : t.outputs)
	{
		j[LABEL_TXS_OUTPUT][count][LABEL_TXS_PUBKEY] = i.publicKey;
		j[LABEL_TXS_OUTPUT][count][LABEL_TXS_AMOUNT] = i.amount;
		count++;
	}
	return j;
}

TransactionS Json2Transactions(json& j)
{
	TransactionS t;
	t.txID = j[LABEL_TXS_TXID].get<string>();
	//**
	t.PubKey = j[LABEL_TXS_PUBKEY].get<string>();
	t.signature = String2ByteVector(j[LABEL_TXS_SIGNATURE].get<string>());
	//**
	for (unsigned int i = 0; i < j[LABEL_TXS_INPUT].size(); i++)
	{
		InputS input;
		input.blockID = j[LABEL_TXS_INPUT][i][LABEL_BLOCK_BLOCK_ID].get<string>();
		input.txID = j[LABEL_TXS_INPUT][i][LABEL_TXS_TXID].get<string>();
		t.inputs.push_back(input);
	}
	for (unsigned int i = 0; i < j[LABEL_TXS_OUTPUT].size(); i++)
	{
		OutputS output;
		output.publicKey = j[LABEL_TXS_OUTPUT][i][LABEL_TXS_PUBKEY].get<string>();
		output.amount = j[LABEL_TXS_OUTPUT][i][LABEL_TXS_AMOUNT].get<double>();
		t.outputs.push_back(output);
	}
	return t;
}

json EdaMerkleBlock2Json(EdaMerkleBlockS& b)
{
	json j;
	j[LABEL_BLOCK_TXS_COUNT] = b.txCount;
	int count = 0;
	for (TransactionS t : b.transactions)
	{
		j[LABEL_BLOCK_TXS][count] = Transactions2Json(t);
		count++;
	}
	count = 0;
	for (MerkleValidationData v : b.merklePathDataForTxs)
	{
		j[LABEL_EDABLOCK_MERKLEDATA][count][LABEL_EDABLOCK_PATHLENGTH] = v.merklePathLen;
		int count2 = 0;
		for (Step s : b.merklePathDataForTxs[count].merklePath)
		{
			j[LABEL_EDABLOCK_MERKLEDATA][count][LABEL_EDABLOCK_STEP][count2][LABEL_EDABLOCK_ID] = s.getID();
			if(s.getDir()==direction::RIGHT)
				j[LABEL_EDABLOCK_MERKLEDATA][count][LABEL_EDABLOCK_STEP][count2][LABEL_EDABLOCK_DIR] = LABEL_EDABLOCK_DIR_R;
			else
				j[LABEL_EDABLOCK_MERKLEDATA][count][LABEL_EDABLOCK_STEP][count2][LABEL_EDABLOCK_DIR] = LABEL_EDABLOCK_DIR_L;
			count2++;
		}
		count++;
	}
	j[LABEL_BLOCK_BLOCK_ID] = b.blockID;
	return j;
}

EdaMerkleBlockS Json2EdaMerkleBlock(json& j)
{
	EdaMerkleBlockS b;
	b.txCount = j[LABEL_BLOCK_TXS_COUNT].get<int>();
	for (unsigned int i = 0; i < j[LABEL_BLOCK_TXS].size(); i++)
	{
		b.transactions.push_back(Json2Transactions(j[LABEL_BLOCK_TXS][i]));
	}
	for (unsigned int i = 0; i < j[LABEL_EDABLOCK_MERKLEDATA].size(); i++)
	{
		MerkleValidationData tempData;
		tempData.merklePathLen= j[LABEL_EDABLOCK_MERKLEDATA][i][LABEL_EDABLOCK_PATHLENGTH].get<int>();
		for (unsigned int k = 0; k < j[LABEL_EDABLOCK_MERKLEDATA][i][LABEL_EDABLOCK_STEP].size(); k++)
		{
			direction dir;
			if (j[LABEL_EDABLOCK_MERKLEDATA][i][LABEL_EDABLOCK_STEP][k][LABEL_EDABLOCK_DIR] == LABEL_EDABLOCK_DIR_R)
				dir = direction::RIGHT;
			else
				dir = direction::LEFT;
			string s = j[LABEL_EDABLOCK_MERKLEDATA][i][LABEL_EDABLOCK_STEP][k][LABEL_EDABLOCK_ID].get<string>();
			Step step(s, dir);
			tempData.merklePath.push_back(step);
		}
		b.merklePathDataForTxs.push_back(tempData);
	}
	b.blockID = j[LABEL_BLOCK_BLOCK_ID].get<string>();

	return b;
}

json Block2Json(Model_Block& b)
{
	json j;
	j[LABEL_BLOCK_BLOCK_ID] = b.getBlockID();
	j[LABEL_BLOCK_PREV_BLOCK_ID] = b.get_previous_blockID();
	j[LABEL_BLOCK_MERKLE_ROOT] = b.getMerkleRoot();
	j[LABEL_BLOCK_TXS_COUNT] = b.getTxsCount();
	int count = 0;
	for (TransactionS t : b.get_transactions())
	{
		j[LABEL_BLOCK_TXS][count] = Transactions2Json(t);
		count++;
	}
	j[LABEL_BLOCK_NOUNCE] = b.getNounce();
	j[LABEL_BLOCK_INDEX] = b.get_index_in_blockchain();

	/*j["Pos_x"] = b.get_pos_x();
	j["Pos_y"] = b.get_pos_y();
	j["Image_w"] = b.get_size_x();
	j["Image_H"] = b.get_size_y();
	//void* p =(void*) b.getMerkleTreeModel();
	string str = to_string((int64_t)b.getMerkleTreeModel());
	j["MyMerkleTreeModel"] = str;*/
	return j;
}

Model_Block Json2Block(json& j)
{
	string BlockId = j[LABEL_BLOCK_BLOCK_ID].get<string>();
	string PrevBlockID = j[LABEL_BLOCK_PREV_BLOCK_ID].get<string>();
	string MerkleRoot = j[LABEL_BLOCK_MERKLE_ROOT].get<string>();
	unsigned int TxCount = j[LABEL_BLOCK_TXS_COUNT].get<unsigned int>();
	vector<TransactionS> t;
	for (unsigned int i = 0; i < j[LABEL_BLOCK_TXS].size(); i++)
	{
		t.push_back(Json2Transactions(j[LABEL_BLOCK_TXS][i]));
	}
	Model_Block b(BlockId, MerkleRoot, TxCount, t);
	b.set_previous_blockID(PrevBlockID);
	//unsigned long nounce = j[LABEL_BLOCK_NOUNCE].get<unsigned long>();
	//unsigned long index_block = j[LABEL_BLOCK_INDEX].get<unsigned long>();
	b.setNounce(j[LABEL_BLOCK_NOUNCE].get<unsigned long>());
	b.set_index_block_in_bchn(j[LABEL_BLOCK_INDEX].get<unsigned long>());
	/*
	b.set_pos_x(j["Pos_x"].get<unsigned int>());
	b.set_pos_y(j["Pos_y"].get<unsigned int>());
	b.set_size_x(j["Image_w"].get<unsigned int>());
	b.set_size_y(j["Image_H"].get<unsigned int>());
	Model_MerkleTree* myMerkleTreeModel = (Model_MerkleTree *)stoll(j["MyMerkleTreeModel"].get<string>());
	b.setMerkleTreeModel(myMerkleTreeModel);
	*/
	return b;
}

json Header2Json(blockHeader& b)
{
	json j;
	j[LABEL_BLOCK_BLOCK_ID] = b.blockID;
	j[LABEL_BLOCK_PREV_BLOCK_ID] = b.prevBlockID;
	j[LABEL_BLOCK_MERKLE_ROOT] = b.merkleRoot;
	j[LABEL_BLOCK_NOUNCE] = b.nounce;
	j[LABEL_BLOCK_INDEX] = b.index;

	return j;
}

blockHeader Json2Header(json& j)
{
	blockHeader b;
	b.blockID = j[LABEL_BLOCK_BLOCK_ID].get<string>();
	b.prevBlockID = j[LABEL_BLOCK_PREV_BLOCK_ID].get<string>();
	b.merkleRoot = j[LABEL_BLOCK_MERKLE_ROOT].get<string>();
	b.nounce = j[LABEL_BLOCK_NOUNCE].get<unsigned long>();
	b.index = j[LABEL_BLOCK_INDEX].get<unsigned int>();
	return b;
}

string Pointer2String(void*p)
{
	string str = to_string((int64_t)p);
	return str;
}

void* String2Pointer(string& str)
{
	void* p = (void*)stoll(str);
	return p;
}