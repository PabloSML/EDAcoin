#include "FormatConverter.h"
#include <iostream>

using namespace std;

json Transactions2Json(TransactionS& t)
{
	json j;
	j["TxID"] = t.txID;
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
		j["Outputs"][count]["PublicID"] = i.publicID;
		j["Outputs"][count]["Amount"] = i.amount;
		count++;
	}
	return j;
}

TransactionS Json2Transactions(json& j)
{
	TransactionS t;
	t.txID = j["TxID"].get<string>();
	for (int i = 0; i < j["Inputs"].size(); i++)
	{
		InputS input;
		input.blockID = j["Inputs"][i]["BlockID"].get<string>();
		input.txID = j["Inputs"][i]["TxID"].get<string>();
		t.inputs.push_back(input);
	}
	for (int i = 0; i < j["Outputs"].size(); i++)
	{
		OutputS output;
		output.publicID = j["Outputs"][i]["PublicID"].get<string>();
		output.amount = j["Outputs"][i]["Amount"].get<int>();
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

EdaMerkleBlockS Json2EdaMerkleBlock(json&j)
{
	EdaMerkleBlockS b;
	b.txCount = j["TxCount"].get<int>();
	for (int i = 0; i < j["Transactions"].size(); i++)
	{
		b.transactions.push_back(Json2Transactions(j["Transactions"][i]));
	}
	for (int i = 0; i < j["MerkleValidationData"].size(); i++)
	{
		MerkleValidationData tempData;
		tempData.merklePathLen= j["MerkleValidationData"][i]["merklePathLen"].get<int>();
		for (int k = 0; k < j["MerkleValidationData"][i]["Step"].size(); k++)
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