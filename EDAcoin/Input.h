#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <vector>



#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;



class Input {

public:

	//builders
	Input(json json_input);
	
	//destroyers
	~Input();

	//setters
	void set_input(string tx_id, string block_id);

	//getters
	string get_block_id(void) const;
	string get_transaction_id(void) const;


	//other functions
	string body(void);
	bool is_transaction_id(string transaction_id);
	bool is_block_id(string block_id);

	//operators
	bool operator==(const Input& i);

private:

	void set_block_id(string block_id);
	void set_transaction_id(string tx_id);
	

	string block_id;
	string transaction_id;

};



#endif // !INPUT_H
