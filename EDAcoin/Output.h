#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>

using namespace std;

class Output {

public:

	//builders
	Output();
	Output(string ID, double amount);
	Output(const Output& copy);

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
