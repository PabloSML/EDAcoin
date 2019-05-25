#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>

using namespace std;

class Input {

public:

	//builders
	Input();
	Input(string tx_id, string block_id);
	Input(const Input& copy);
	
	//destroyers
	~Input();

	//setters
	void set_input(string tx_id, string block_id);

	//getters
	string get_block_id(void) const;
	string get_transaction_id(void) const;


	//other functions
	string body(void);

	//operators
	bool operator==(const Input& i);

private:

	void set_block_id(string block_id);
	void set_transaction_id(string tx_id);
	

	string block_id;
	string transaction_id;

};



#endif // !INPUT_H
