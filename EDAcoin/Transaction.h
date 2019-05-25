#ifndef TRANSACTION_H
#define TRANSACTION_H


#pragma once

#include <string>
#include <list>

#include "Input.h"
#include "Output.h"

using namespace std;

class Transaction {

public:

	//builders
	Transaction(void);
	Transaction(string id, list<Input> inputs, list<Output> outputs);
	Transaction(const Transaction& copy);

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



