#include <stdio.h>
#include <string.h>
#include "struct_data.h"
#include "write_to_file.h"
#include "read_from_file.h"


int main(void) {
    FILE *record = fopen("record.dat", "w");
    FILE *transaction = fopen("transaction.dat", "w");
    FILE *blackrecord = fopen("blackrecord.dat", "w");
    data expected_client_data = { .number = 1,
		.name = "Artur",
		.surname = "King",
		.addres = "Camelot",
		.telephone_number = "no_phone_number",
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
		.telephone_number = "no_phone_number",
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
    fclose(record);
    fclose(transaction);
    fclose(blackrecord);
    record = fopen("record.dat", "r");
    transaction = fopen("transaction.dat", "r");
    blackrecord = fopen("blackrecord.dat", "r");
    read_from_file(record, &got_client_data, 1);
    read_from_file(transaction, &got_transfer, 2);
    read_from_file(blackrecord, &got_updated_credit_limit, 3);
    fclose(record);
    fclose(transaction);
    fclose(blackrecord);
    float flag = 0;  // Позволяет вывести обощающее сообщение об успехе тестов
    if (expected_client_data.number != got_client_data.number)  // Сравнение ожидаемых и полученных результатов
        puts("File record: number test failed");
    else if (strncmp(expected_client_data.name, got_client_data.name, 25) != 0)
        puts("File record: name test failed");
    else if (strncmp(expected_client_data.surname, got_client_data.surname, 25) != 0)
        puts("File record: surname test failed");
    else if (strncmp(expected_client_data.telephone_number, got_client_data.telephone_number, 20) != 0)
        puts("File record: telephone_number test failed");
    else if (strncmp(expected_client_data.addres, got_client_data.addres, 35) != 0)
        puts("File record: addres test failed");
    else if (expected_client_data.indebtedness != got_client_data.indebtedness)
        puts("File record: indebtedness test failed");
    else if (expected_client_data.credit_limit != got_client_data.credit_limit)
        puts("File record: credit_limit test failed");
    else if (expected_client_data.cash_payments != got_client_data.cash_payments)
        puts("File record: cash_payments test failed");
    else {
        flag += 0.5;
        puts("File record test if successful");
    }
    if (expected_transfer.number != got_transfer.number)
        puts("File transaction: number test failed");
    else if (expected_transfer.cash_payments != got_transfer.cash_payments)
        puts("File transaction: cash_payments test failed");
    else {
        flag += 0.25;
        puts("File transaction test is successful");
    }
    if (expected_updated_credit_limit.number != got_updated_credit_limit.number)
        puts("File blackrecord: number test failed");
    else if (strncmp(expected_updated_credit_limit.name, got_updated_credit_limit.name, 25) != 0)
        puts("File blackrecord: name test failed");
    else if (strncmp(expected_updated_credit_limit.surname, got_updated_credit_limit.surname, 25) != 0)
        puts("File blackrecord: surname test failed");
    else if (strncmp(expected_updated_credit_limit.telephone_number, got_updated_credit_limit.telephone_number, 20) != 0)
        puts("File blackrecord: telephone_number test failed");
    else if (strncmp(expected_updated_credit_limit.addres, got_updated_credit_limit.addres, 35) != 0)
        puts("File blackrecord: addres test failed");
    else if (expected_updated_credit_limit.indebtedness != got_client_data.indebtedness)
        puts("File blackrecord: indebtedness test failed");
    else if (expected_updated_credit_limit.credit_limit != got_updated_credit_limit.credit_limit)
        puts("File blackrecord: credit_limit test failed");
    else if (expected_updated_credit_limit.cash_payments != got_updated_credit_limit.cash_payments)
        puts("File blackrecord: cash_payments test failed");
    else {
        flag += 0.25;   
        puts("File blackrecord test if successful");
    }
    if (flag == 1)
        puts("******ALL TESTS ARE SUCCESSFUL******");
    return 0;
}
