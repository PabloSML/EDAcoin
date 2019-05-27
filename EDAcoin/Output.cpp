#include "Output.h"
#include "Labels.h"

//builders
Output::
Output(json json_output) {
	this->id_output = string(json_output[LABEL_OUTPUT_ID]);
	this->amount = stod(string(json_output[LABEL_OUTPUT_AMOUNT]));
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

bool Output::
is_output_id(string output_id)
{
	bool is_id_bool = false;

	if (!((this->id_output).compare(output_id)))
	{
		is_id_bool = true;
	}

	return is_id_bool;
}

//operators
bool Output::
operator==(const Output& output) {
	bool ret;
	ret = (output.amount == this->amount) && (output.id_output == this->id_output);
	return ret;
}




