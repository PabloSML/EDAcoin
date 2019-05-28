#include "Transaction.h"
#include "Labels.h"

//builders

Transaction::
Transaction(json json_transaction) {

	this->id = json_transaction[LABEL_TXS_TXID].get<string>();

	for (int i = 0; i < (json_transaction[LABEL_TXS_INPUT]).size(); i++)
	{
		Input temp_input(json_transaction[LABEL_TXS_INPUT][i]);
		(this->inputs).push_back(temp_input);
	}

	for (int i = 0; i < (json_transaction[LABEL_TXS_OUTPUT]).size(); i++)
	{
		Output temp_output(json_transaction[LABEL_TXS_OUTPUT][i]);
		(this->outputs).push_back(temp_output);
	}

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

bool Transaction::
does_appear_ID(string ID_node)
{
	bool appear_ID = false;

	vector<Input> temp_inputs = this->inputs;
	vector<Output> temp_outputs = this->outputs;

	unsigned int cant_inputs_tx_i = (unsigned int) temp_inputs.size();
	unsigned int cant_outputs_tx_i = (unsigned int) temp_outputs.size();


	for (unsigned int input = 0; (input < cant_inputs_tx_i) && (!appear_ID); input++)
	{
		if ((temp_inputs[input]).is_transaction_id(ID_node))
		{
			appear_ID = true;
		}
	}


	for (unsigned int output = 0; (output < cant_outputs_tx_i) && (!appear_ID); output++)
	{
		if ((temp_outputs[output]).is_output_id(ID_node))
		{
			appear_ID = true;
		}
	}

	return appear_ID;

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

