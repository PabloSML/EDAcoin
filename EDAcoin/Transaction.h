#ifndef TRANSACTION_H
#define TRANSACTION_H


#pragma once

#include <string>
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
	Transaction(void);
	Transaction(string id, list<Input> inputs, list<Output> outputs);
	Transaction(const Transaction& copy);
	Transaction(json jsonTransaction); // Falta hacer

	//destroyers
	~Transaction(void);

	//setters
	void set_transaction(string id, list<Input> list_input, list<Output> list_output);
	void set_id(string id);
	void set_inputs(list<Input> input);
	void set_outputs(list<Output> list_output);

	//getters
	string get_id(void) const;
	list<Input> get_inputs(void) const;
	list<Output> get_outputs(void) const;

	//others functions
	bool add_input(const Input& input);	   //"setter"
	bool add_output(const Output& output); //"setter"
	void clear(void);
	string body(void);

	//operators
	bool operator==(Transaction& op);

private:
	string id;
	list<Input> inputs;
	list<Output> outputs;
};






#endif // !TRANSACTION_H



