#ifndef TRANSACTION_H
#define TRANSACTION_H


#pragma once

#include <vector>
#include <list>
#include <nlohmann/json.hpp>
#include "Input.h"
#include "Output.h"


//poner json
using namespace std;
using json = nlohmann::json;

class Transaction {

public:

	//builders
	Transaction(json json_transaction);

	//destroyers
	~Transaction(void);

	//setters
	void set_transaction(string id, vector<Input> list_input, vector<Output> list_output);
	void set_id(string id);
	void set_inputs(vector<Input> input);
	void set_outputs(vector<Output> list_output);

	//getters
	string get_id(void) const;
	vector<Input> get_inputs(void) const;
	vector<Output> get_outputs(void) const;

	//others functions
	bool add_input(const Input& input);	   //"setter"
	bool add_output(const Output& output); //"setter"
	void clear(void);
	string body(void);
	bool does_appear_ID(string ID);


	//operators
	bool operator==(Transaction& op);

private:
	string id;
	vector<Input> inputs;
	vector<Output> outputs;
};






#endif // !TRANSACTION_H



