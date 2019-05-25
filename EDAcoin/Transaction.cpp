#include "Transaction.h"

//builders
Transaction::
Transaction(void) {

}

Transaction::
Transaction(string id, Input& input, list<Output> outputs) {
	this->set_transaction(id, input, outputs);
}

Transaction::
Transaction(string id, Input& input, Output& output) {
	list<Output> aux;
	aux.push_back(output);

	this->set_transaction(id, input, aux);
}

Transaction::
Transaction(const Transaction& copy) {
	this->set_transaction(copy.id, copy.input, copy.outputs);
}

//destroyers
Transaction::
~Transaction(void) {

}

//setters
void Transaction::
set_transaction(string id, Input input, list<Output> list_output) {
	this->set_id(id);
	this->set_input(input);
	this->set_outputs(list_output);
}

void Transaction::
set_id(string id) {
	this->id = id;
}

void Transaction::
set_input(const Input& input) {
	this->input = input;
}


void Transaction::
set_outputs(list<Output> list_output) {
	this->outputs = list_output;
}

//getters
string Transaction::
get_id(void) const {
	return this->id;
}

Input Transaction::
get_input(void) const {
	return this->input;
}

list<Output> Transaction::
get_outputs(void) const {
	return this->outputs;
}


//others functions
bool Transaction::
add_output(const Output& output) { //"setter"

	try {
		this->outputs.push_back(output);
		return true;
	}
	catch (...) {
		return false;
	}

}

void Transaction::
clear(void) {
	
	this->id = "";
	this->input = Input();
	
	this->outputs.clear();

}

string Transaction::
body(void) {
	string body;
	body = this->id;
	body += (this->input).body();
	
	for (Output output : this->outputs) {
		body += output.body();
	}

	return body;
}


//operators
bool Transaction::
operator==(Transaction& op) {

	bool ret;
	

	ret = (this->id == op.id) && (this->input == op.input);

	if (ret == true)
	{
		if (outputs.size() == op.outputs.size()) {

			bool found;

			for (Output out : this->outputs) {

				found = false;

				for (Output out_copy : op.outputs) {

					if (out == out_copy) {
						found = true;
						break;
					}
				}

				if (!found) {
					ret = false;
				}
			}
		}
		else
		{
			ret = false;
		}
	} 

	return ret;

	
}


