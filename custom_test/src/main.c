#include <stdio.h>
#include "struct_data.h"

int main(void) {
    pointer_to_file_record = fopen("record.dat", "r+");
    pointer_to_file_record = fopen("transaction.dat", "r+");
    pointer_to_file_blackrecord = fopen("blackrecord.dat", "w+");
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
    data got_updated_credit_limit = { .number = 0,
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
    write_to_file(pointer_to_file_blackrecord, expected_updated_credit_limit, 3);
    read_from_file(pointer_to_file_record, &got_client_data, 1);
    read_from_file(pointer_to_file_transaction, &got_transfer, 2);
    read_from_file(pointer_to_file_blackrecord, &got_updated_credit_limit, 3);
    int flag = 1;
    if ((expected_client_data.name != got_client_data.name) || (expected_client_data.surname != got_client_data.surname) \
    || (expected_client_data.addres != got_client_data.addres) || (expected_client_data.telephone_number != got_client_data.telephone_number) \
    || (expected_client_data.indebtedness != got_client_data.indebtedness) || (expected_client_data.credit_limit != got_client_data.credit_limit) \
    || (expected_client_data.cash_payments != got_client_data.cash_payments) || (expected_client_data.cash_payments != got_client_data.cash_payments)) {
        printf("Error: record.dat file mismatch")
        flag = 0;
    if ((expected_transfer.number != got_transfer.number) || (expected_transfer.cash_payments != got_transfer.cash_payments)) {
        printf("Error: transaction.dat file mismatch")
        flag = 0;
    if ((expected_updated_credit_limit.name != got_updated_credit_limit.name) || (expected_updated_credit_limit.surname != got_updated_credit_limit.surname) \
    || (expected_updated_credit_limit.addres != got_updated_credit_limit.addres) || (expected_updated_credit_limit.telephone_number != got_updated_credit_limit.telephone_number) \
    || (expected_updated_credit_limit.indebtedness != got_updated_credit_limit.indebtedness) || (expected_updated_credit_limit.credit_limit != got_updated_credit_limit.credit_limit) \
    || (expected_updated_credit_limit.cash_payments != got_updated_credit_limit.cash_payments) || (expected_client_data.expected_updated_credit_limit != got_updated_credit_limit.cash_payments)) {
        printf("Error: record.dat file mismatch")
        flag = 0;    
    }
    }
    if (flag)
        print("The test is successful")
    fclose(pointer_to_file_record);
    fclose(pointer_to_file_transaction);
    fclose(pointer_to_file_blackrecord);
}
