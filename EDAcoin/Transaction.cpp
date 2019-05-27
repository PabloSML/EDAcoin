#include "Transaction.h"

//builders

Transaction::
Transaction(json json_transaction) {

	this->id = string(json_transaction["TxID"]);


	Input temp_input(json_transaction["input"]);
	(this->inputs).push_back(temp_input);

	Output temp_output(json_transaction["output"]);
	(this->outputs).push_back(temp_output);

}


//destroyers
Transaction::
~Transaction(void) {

}

//setters
void Transaction::
set_transaction(string id, vector<Input> list_input, vector<Output> list_output) {
	this->set_id(id);
	this->set_inputs(list_input);
	this->set_outputs(list_output);
}

void Transaction::
set_id(string id) {
	this->id = id;
}

void Transaction::
set_inputs(vector<Input> list_input) {
	this->inputs = list_input;
}


void Transaction::
set_outputs(vector<Output> list_output) {
	this->outputs = list_output;
}

//getters
string Transaction::
get_id(void) const {
	return this->id;
}

vector<Input> Transaction::
get_inputs(void) const {
	return this->inputs;
}

vector<Output> Transaction::
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

