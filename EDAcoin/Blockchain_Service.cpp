#include "Blockchain_Service.h"

blockchain_service::
blockchain_service(vector<UTXO>* _utxos) : utxos(_utxos) {

}

blockchain_service::
~blockchain_service(void) {

}




double blockchain_service::
fetch_balance(string who_i_want_balance) {

	double balance_resquest = 0;

	for (UTXO utxo : *utxos) {

		if ((utxo.get_output()).publicID.compare(who_i_want_balance) == 0) {

			balance_resquest += utxo.get_output().amount;
		}
	}

	return balance_resquest;
}


vector<UTXO> blockchain_service::
fetch_utxos(string who_i_want_utxos) {

	vector<UTXO> utxos_request;
	utxos_request.clear();

	for (UTXO utxo : *utxos) {

		if ((utxo.get_output()).publicID.compare(who_i_want_utxos) == 0) {
			utxos_request.push_back(utxo);
		}
	}

	return utxos_request;
}



//creo una transaccion de uno a uno
bool blockchain_service:: 
create_transaction(
	string from,
	string to,
	double amount,
	TransactionS& new_transaction ) {

	bool all_ok = true;


	vector<InputS> inputs;
	vector<OutputS> outputs;
	new_transaction = { "","", inputs, outputs };



	vector <UTXO> from_utxo = fetch_utxos(from);

	double min_amount = amount;

	if (get_amount(from_utxo) >= (min_amount)) {

		double in_amount = 0;
		vector<UTXO>::iterator itr = from_utxo.begin();

		while (in_amount < (min_amount)) {

			InputS aux_input;
			
			aux_input.blockID = itr->get_blockID();
			aux_input.txID = itr->get_txID();

			new_transaction.inputs.push_back(aux_input);

			in_amount += itr->get_output().amount;

			itr++;
		}

		OutputS aux_output;
		aux_output.amount = amount;
		aux_output.publicID = to;

		new_transaction.outputs.push_back(aux_output);

	}
	else
	{
		all_ok = false;
	}

	return all_ok;
}







double blockchain_service::
get_amount(vector<UTXO>& utxos) {

	double amount = 0;

	for (UTXO utxo : utxos) {
		amount += (utxo.get_output()).amount;
	}

	return amount;
}

blockchain_message blockchain_service::
create_blockchain_message(TransactionS transaction) {
	
	blockchain_message message;

	type_message type = type_message::NEW_TRANSACTION;

	message = blockchain_message(type, transaction);

	return message;
}


