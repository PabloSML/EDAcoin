#pragma once


#include "UTXO.h"

#include "Blockchain_Message.h"

#include "Definitions.h"

#include <vector>
#include <string>

using namespace std;


class blockchain_service {

public:

	blockchain_service(vector<UTXO>& utxos);
	~blockchain_service(void);


	double fetch_balance(string who_i_want_balance);

	vector<UTXO> fetch_utxos(string who_i_want_utxos);

	bool create_transaction( //creo una transaccion de uno a uno
		string  from,
		string to,
		double amount,
		TransactionS& new_transaction
	);


	blockchain_message create_blockchain_message(TransactionS transaction);
	

private:
	double get_amount(vector<UTXO>& utxos);

	vector<UTXO>& utxos;
};