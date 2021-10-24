#include <stdio.h>
#include "struct_data.h"

int main(void) {
    pointer_to_file_record = fopen("record.dat", "r+");
    pointer_to_file_record = fopen("transaction.dat", "r+");
    pointer_to_file_blackrecord = fopen("blackrecord.dat", "w");
    data expected_client_data = { .number = 1,
		.name = "Artur",
		.surname = "King",
		.adress = "Camelot",
		.telephone_number = "no phone number",
		.indebtedness = 240,
		.credit_limit = 300000,
		.cash_payments = 6700000
	};
    data expected_transfer = {.number = 1,
		.cash_payments = 45000
	};
    data expected_updated_credit_limit = { .number = 1,
		.name = "Artur",
		.surname = "King",
		.adress = "Camelot",
		.telephone_number = "no phone number",
		.indebtedness = 240,
		.credit_limit = 345000,
		.cash_payments = 6700000
	};
    data got_client_data = { .number = 0,
		.name = "Client name",
		.surname = "Client surname",
		.adress = "Client adress",
		.telephone_number = "Client t number",
		.indebtedness = 0,
		.credit_limit = 0,
		.cash_payments = 0
	};
    data got_transfer = {.number = 0,
		.cash_payments= 0
	};
    data got_client_data = { .number = 0,
		.name = "Client name",
		.surname = "Client surname",
		.adress = "Client adress",
		.telephone_number = "Client t number",
		.indebtedness = 0,
		.credit_limit = 0,
		.cash_payments = 0
	};
    write_to_file(pointer_to_file_record, expected_client_data, 1);
    write_to_file(pointer_to_file_transaction, expected_transfer, 2);
    write_to_file_blackrecord(pointer_to_file_record, pointer_to_file_transaction, pointer_to_file_blackrecord, expected_client_data, expected_updated_credit_limit);

    fclose(pointer_to_file_record);
    fclose(pointer_to_file_transaction);
    fclose(pointer_to_file_blackrecord);
