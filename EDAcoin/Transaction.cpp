#include "Transaction.h"

//builders
Transaction::
Transaction(void) {

}

Transaction::
Transaction(string id, list<Input> inputs, list<Output> outputs) {
	this->set_transaction(id, inputs, outputs);
}


Transaction::
Transaction(const Transaction& copy) {
	this->set_transaction(copy.id, copy.inputs, copy.outputs);
}

//destroyers
Transaction::
~Transaction(void) {

}

//setters
void Transaction::
set_transaction(string id, list<Input> list_input, list<Output> list_output) {
	this->set_id(id);
	this->set_inputs(list_input);
	this->set_outputs(list_output);
}

void Transaction::
set_id(string id) {
	this->id = id;
}

void Transaction::
set_inputs(list<Input> list_input) {
	this->inputs = list_input;
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

list<Input> Transaction::
get_inputs(void) const {
	return this->inputs;
}

list<Output> Transaction::
get_outputs(void) const {
	return this->outputs;
}


//others functions
bool Transaction::
add_input(const Input& input) { //"setter"

	try {
		this->inputs.push_back(input);
		return true;
	}
	catch (...) {
		return false;
	}

}

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

	this->inputs.clear();
	this->outputs.clear();
}

string Transaction::
body(void) {
	string body;
	body = this->id;

	for (Input input : this->inputs) {
		body += input.body();
	}

	body += to_string((this->inputs).size());
	
	for (Output output : this->outputs) {
		body += output.body();
	}

	body += to_string((this->outputs).size());

	return body;
}


//operators
bool Transaction::
operator==(Transaction& op) {

	bool ret;


	ret = (this->id == op.id);

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

	if (ret == true)
	{
		if (inputs.size() == op.inputs.size()) {

			bool found;

			for (Input input : this->inputs) {

				found = false;

				for (Input input_copy : op.inputs) {

					if (input == input_copy) {
						found = true;
						break;
					}
				}

				if (!found) {
					ret = false;
				}
			}
		}
	}
		return ret;
}

