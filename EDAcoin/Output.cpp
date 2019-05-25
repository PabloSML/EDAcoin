#include "Output.h"


//builders
Output::
Output()
{
	this->amount = 0;
}

Output::
Output(string ID, double amount) {

	this->set_output(ID, amount);
}

Output::
Output(const Output& copy) {
	this->set_output(copy.id_output, copy.amount);
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




