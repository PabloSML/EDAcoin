#include "UTXO.h"


UTXO::
UTXO() {
	this->blockID = "";
	this->txID = "";
}

UTXO::
UTXO(string new_blockID, string new_txID, OutputS new_output):blockID(new_blockID), txID(new_txID),output(new_output) {
	
}


UTXO::
~UTXO() {

}

void UTXO::
set_reference(string new_blockID, string new_txID) {
	this->blockID = new_blockID;
	this->txID = new_txID;
}

void UTXO::
set_output(OutputS new_output) {
	this->output = new_output;
}

string UTXO::
get_blockID(void) const {
	return this->blockID;
}

string UTXO::
get_txID(void) const {

	return this->txID;
}

OutputS UTXO::
get_output(void) const {

	return this->output;
}

