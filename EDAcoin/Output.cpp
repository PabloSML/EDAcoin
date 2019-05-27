#include "Output.h"


//builders
Output::
Output(json json_output) {

	this->id_output = string(json_output["publicKey"]);
	this->amount = stod(string(json_output["EDACoins"]));
	
}



//destroyers
Output::
~Output()
{

}


//setters
void Output::
set_output(string ID, double amount) {
	this->set_id_output(ID);
	this->set_amount(amount);
}


void Output::
set_amount(double amount) {
	this->amount = amount;
}

void Output::
set_id_output(string id_output) {
	this->id_output = id_output;
}


//getters
string Output::
get_id_output(void) {
	return this->id_output;
}

double Output::
get_amount(void) {
	return this->amount;
}


//others functions
string Output::
body(void) {
	string body = this->id_output + to_string(this->amount);
	return body;
}

//operators
bool Output::
operator==(const Output& output) {
	bool ret;
	ret = (output.amount == this->amount) && (output.id_output == this->id_output);
	return ret;
}




