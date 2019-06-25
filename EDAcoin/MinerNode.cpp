#include "MinerNode.h"

bool
MinerNode::analizePackage(netPckg package)
{
	bool isPackageNew = false;

	if (package.data.contains(LABEL_BLOCK_BLOCK_ID))	// es un Bloque
	{
		bool found = false;
		string newBlockID = package.data[LABEL_BLOCK_BLOCK_ID].get<string>();

		if (!blockChain.empty())
		{
			vector<Model_Block*>::reverse_iterator ritr = blockChain.rbegin();
			for (ritr; ritr < blockChain.rend() && !found; ritr++)
			{
				if (newBlockID == (*ritr)->getBlockID())
				{
					found = true;
				}
			}
		}

		if (!found)
		{
			isPackageNew = true;
			floodingQueue.push(package);
			recieveBlock(package.data);
			sendInfo2Spv();
		}
	}

	else if (package.data.contains(LABEL_TXS_TXID))  // es una Tx
	{
		bool found = false;
		string newTxID = package.data[LABEL_TXS_TXID].get<string>();

		if (!jsonTxs.empty())
		{
			vector<json>::reverse_iterator ritr2 = jsonTxs.rbegin();
			for (ritr2; ritr2 < jsonTxs.rend() && !found; ritr2++)
			{
				if (newTxID == (*ritr2)[LABEL_TXS_TXID].get<string>())
				{
					found = true;
				}
			}
		}

		if (!found)
		{
			isPackageNew = true;
			floodingQueue.push(package);
			jsonTxs.push_back(package.data);
			if (miningBlock != nullptr)
			{
				TransactionS tempTx = Json2Transactions(package.data);
				miningBlock->addTransaction(tempTx);
			}
		}
	}

	return isPackageNew;
}