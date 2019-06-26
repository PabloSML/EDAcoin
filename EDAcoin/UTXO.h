#pragma once

#include <string>

#include "Definitions.h"

using namespace std;

class UTXO {

public:

	UTXO(string blockID, string txID, OutputS output);
	UTXO();
	~UTXO();


	void set_reference(string blockID, string txID);
	void set_output(OutputS output);

	
	string get_blockID(void) const;
	string get_txID(void) const;
	OutputS get_output(void) const;

	bool operator==(UTXO utxo_compare);

private:

	string blockID;
	string txID;
	OutputS output;
};
