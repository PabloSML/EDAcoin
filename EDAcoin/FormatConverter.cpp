#include "FormatConverter.h"
#include <iostream>
#include <stdint.h>

using namespace std;

json Transactions2Json(TransactionS& t)
{
	json j;
	j["TxID"] = t.txID;
	//**
	j["PublicKey"] =t.PubKey;
	j["Signature"] = ByteVector2String(t.signature);
	//**
	int count = 0;
	for (InputS i : t.inputs)
	{
		j["Inputs"][count]["BlockID"] = i.blockID;
		j["Inputs"][count]["TxID"] = i.txID;
		count++;
	}
	count = 0;
	for (OutputS i : t.outputs)
	{
		j["Outputs"][count]["PublicKey"] = i.publicKey;
		j["Outputs"][count]["Amount"] = i.amount;
		count++;
	}
	return j;
}

TransactionS Json2Transactions(json& j)
{
	TransactionS t;
	t.txID = j["TxID"].get<string>();
	//**
	t.PubKey = j["PublicKey"].get<string>();
	t.signature = String2ByteVector(j["Signature"].get<string>());
	//**
	for (unsigned int i = 0; i < j["Inputs"].size(); i++)
	{
		InputS input;
		input.blockID = j["Inputs"][i]["BlockID"].get<string>();
		input.txID = j["Inputs"][i]["TxID"].get<string>();
		t.inputs.push_back(input);
	}
	for (unsigned int i = 0; i < j["Outputs"].size(); i++)
	{
		OutputS output;
		output.publicKey = j["Outputs"][i]["PublicKey"].get<string>();
		output.amount = j["Outputs"][i]["Amount"].get<double>();
		t.outputs.push_back(output);
	}
	return t;
}

json EdaMerkleBlock2Json(EdaMerkleBlockS& b)
{
	json j;
	j["TxCount"] = b.txCount;
	int count = 0;
	for (TransactionS t : b.transactions)
	{
		j["Transactions"][count] = Transactions2Json(t);
		count++;
	}
	count = 0;
	for (MerkleValidationData v : b.merklePathDataForTxs)
	{
		j["MerkleValidationData"][count]["merklePathLen"] = v.merklePathLen;
		int count2 = 0;
		for (Step s : b.merklePathDataForTxs[count].merklePath)
		{
			j["MerkleValidationData"][count]["Step"][count2]["ID"] = s.getID();
			if(s.getDir()==direction::RIGHT)
				j["MerkleValidationData"][count]["Step"][count2]["Direction"] = "Right";
			else
				j["MerkleValidationData"][count]["Step"][count2]["Direction"] = "Left";
			count2++;
		}
		count++;
	}
	j["BlockID"] = b.blockID;
	return j;
}

EdaMerkleBlockS Json2EdaMerkleBlock(json& j)
{
	EdaMerkleBlockS b;
	b.txCount = j["TxCount"].get<int>();
	for (unsigned int i = 0; i < j["Transactions"].size(); i++)
	{
		b.transactions.push_back(Json2Transactions(j["Transactions"][i]));
	}
	for (unsigned int i = 0; i < j["MerkleValidationData"].size(); i++)
	{
		MerkleValidationData tempData;
		tempData.merklePathLen= j["MerkleValidationData"][i]["merklePathLen"].get<int>();
		for (unsigned int k = 0; k < j["MerkleValidationData"][i]["Step"].size(); k++)
		{
			direction dir;
			if (j["MerkleValidationData"][i]["Step"][k]["Direction"] == "Right")
				dir = direction::RIGHT;
			else
				dir = direction::LEFT;
			string s = j["MerkleValidationData"][i]["Step"][k]["ID"].get<string>();
			Step step(s, dir);
			tempData.merklePath.push_back(step);
		}
		b.merklePathDataForTxs.push_back(tempData);
	}
	b.blockID = j["BlockID"].get<string>();

	return b;
}

json Block2Json(Model_Block& b)
{
	json j;
	j["BlockID"] = b.getBlockID();
	j["PrevBlockID"] = b.get_previous_blockID();
	j["MerkleRoot"] = b.getMerkleRoot();
	j["TxCount"] = b.getTxsCount();
	int count = 0;
	for (TransactionS t : b.get_transactions())
	{
		j["Transactions"][count] = Transactions2Json(t);
		count++;
	}
	j["Nounce"] = b.getNounce();
	j["IndexBlock"] = b.get_index_in_blockchain();

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
	string BlockId = j["BlockID"].get<string>();
	string PrevBlockID = j["PrevBlockID"].get<string>();
	string MerkleRoot = j["MerkleRoot"].get<string>();
	unsigned int TxCount = j["TxCount"].get<unsigned int>();
	vector<TransactionS> t;
	for (unsigned int i = 0; i < j["Transactions"].size(); i++)
	{
		t.push_back(Json2Transactions(j["Transactions"][i]));
	}
	Model_Block b(BlockId, MerkleRoot, TxCount, t);
	b.set_previous_blockID(PrevBlockID);
	//unsigned long nounce = j["Nounce"].get<unsigned long>();
	//unsigned long index_block = j["IndexBlock"].get<unsigned long>();
	b.setNounce(j["Nounce"].get<unsigned long>());
	b.set_index_block_in_bchn(j["IndexBlock"].get<unsigned long>());
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
	j["BlockID"] = b.blockID;
	j["PrevBlockID"] = b.prevBlockID;
	j["MerkleRoot"] = b.merkleRoot;
	j["Nounce"] = b.nounce;
	j["IndexBlock"] = b.index;

	return j;
}

blockHeader Json2Header(json& j)
{
	blockHeader b;
	b.blockID = j["BlockID"].get<string>();
	b.prevBlockID = j["PrevBlockID"].get<string>();
	b.merkleRoot = j["MerkleRoot"].get<string>();
	b.nounce = j["Nounce"].get<unsigned long>();
	b.index = j["IndexBlock"].get<unsigned int>();
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