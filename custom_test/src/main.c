#include <stdio.h>
#include "struct_data.h"
#include "read_from_file.h"
#include "write_to_file.h"

int main(void) {
    FILE *record = fopen("record.dat", "w+");
    FILE *transaction = fopen("transaction.dat", "w+");
    FILE *blackrecord = fopen("blackrecord.dat", "w+");
    data expected_client_data = { .number = 1,
		.name = "Artur",
		.surname = "King",
		.addres = "Camelot",
		.telephone_number = "no phone number",
		.indebtedness = 240,
		.credit_limit = 300000,
		.cash_payments = 6700000
	};
    data expected_transfer = {.number = 1,
		.cash_payments = 45000
	};
    data expected_updated_credit_limit = {.number = 1,
		.name = "Artur",
		.surname = "King",
		.addres = "Camelot",
		.telephone_number = "no phone number",
		.indebtedness = 240,
		.credit_limit = 345000,
		.cash_payments = 6700000
	};
    data got_client_data = { .number = 0,
		.name = "Client name",
		.surname = "Client surname",
		.addres = "Client addres",
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
		.addres = "Client addres",
		.telephone_number = "Client t number",
		.indebtedness = 0,
		.credit_limit = 0,
		.cash_payments = 0
	};
    write_to_file(record, expected_client_data, 1);
    write_to_file(transaction, expected_transfer, 2);
    write_to_file(blackrecord, expected_updated_credit_limit, 3);
    read_from_file(record, &got_client_data, 1);
    read_from_file(transaction, &got_transfer, 2);
    read_from_file(blackrecord, &got_updated_credit_limit, 3);
    int flag = 1;
    if ((expected_client_data.number != got_client_data.number) || (strncmp((expected_client_data.name, got_client_data.name), 25) != 0) || (strncmp((expected_client_data.surname, got_client_data.surname), 35) != 0) \
    || (strncmp((expected_client_data.addres, got_client_data.addres), 25) != 0) || (strncmp((expected_client_data.telephone_number, got_client_data.telephone_number), 25) != 0) \
    || (strncmp((expected_client_data.surname, got_client_data.surname), 25) != 0) || (expected_client_data.credit_limit != got_client_data.credit_limit) \
    || (expected_client_data.indebtedness != got_client_data.indebtedness) || (expected_client_data.cash_payments != got_client_data.cash_payments)) {
        printf("Error: record.dat file mismatch");
        flag = 0;
    }
    if ((expected_transfer.number != got_transfer.number) || (expected_transfer.cash_payments != got_transfer.cash_payments)) {
        printf("Error: transaction.dat file mismatch");
        flag = 0;
    }
    if ((expected_updated_credit_limit.number != got_updated_credit_limit.number) || (strncmp((expected_updated_credit_limit.name, got_updated_credit_limit.name), 25) != 0) || (strncmp((expected_updated_credit_limit.surname, got_updated_credit_limit.surname), 35) != 0) \
    || (strncmp((expected_updated_credit_limit.addres, got_updated_credit_limit.addres), 25) != 0) || (strncmp((expected_updated_credit_limit.telephone_number, got_updated_credit_limit.telephone_number), 25) != 0) \
    || (strncmp((expected_client_data.surname, got_updated_credit_limit.surname), 25) != 0) || (expected_client_data.credit_limit != got_updated_credit_limit.credit_limit) \
    || (expected_updated_credit_limit.indebtedness != got_updated_credit_limit.indebtedness) || (expected_updated_credit_limit.cash_payments != got_updated_credit_limit.cash_payments)) {
        printf("Error: record.dat file mismatch");
        flag = 0;    
    }
    if (flag)
        print("The test is successful");
    fclose(record);
    fclose(transaction);
    fclose(blackrecord);
    return 0;
}
