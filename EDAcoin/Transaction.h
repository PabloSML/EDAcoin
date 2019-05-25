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
	Transaction(string id, Input& input, list<Output> outputs);
	Transaction(string id, Input& input, Output& output);
	Transaction(const Transaction& copy);

	//destroyers
	~Transaction(void);

	//setters
	void set_transaction(string id, Input input, list<Output> list_output);
	void set_id(string id);
	void set_input(const Input& input);
	void set_outputs(list<Output> list_output);

	//getters
	string get_id(void) const;
	Input get_input(void) const;
	list<Output> get_outputs(void) const;

	//others functions
	bool add_output(const Output& output); //"setter"
	void clear(void);
	string body(void);

	//operators
	bool operator==(Transaction& op);

private:
	string id;
	Input input;
	list<Output> outputs;
};






#endif // !TRANSACTION_H



