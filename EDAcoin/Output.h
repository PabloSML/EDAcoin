#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>


#include <nlohmann/json.hpp>
using namespace std;
using json = nlohmann::json;

class Output {

public:

	//builders
	Output(json json_output);

	//destroyers
	~Output();


	//setters
	void set_output(string ID, double amount);

	//getters
	string get_id_output(void);
	double get_amount(void);


	//others functions
	string body(void);

	//operators
	bool operator==(const Output& output);

private:

	void set_amount(double amount);
	void set_id_output(string id_output);


	string id_output;
	double amount;
	
};


#endif // !OUTPUT_H
