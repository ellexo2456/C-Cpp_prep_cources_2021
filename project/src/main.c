#include <stdio.h>
#include "add_client_data.h"
#include "add_transaction_data.h"
#include "update_credit_limit.h"
#include "struct_data.h"
#define ADD_CLIENT_DATA case 1
#define ADD_TRANSACTION_DATA case 2
#define UPDATE_CREDIT_LIMIT case 3

// Тестирущий модуль сделан через (1): .sh файл и (2)...
// (1) запускать командой make -f TestMakefile из терминала

int main(void) {
	int choice = 0;
	FILE *pointer_to_file_record;
	FILE *pointer_to_file_transaction;
	FILE *pointer_to_file_blackrecord;
	data client_data = { .number = 0,
		.name = "Client name",
		.surname = "Client surname",
		.adress = "Client adress",
		.telephone_number = "Client t number",
		.indebtedness = 0,
		.credit_limit = 0,
		.cash_payments = 0
	};
	data transfer = {.number = 0,
		.cash_payments= 0
	};
	printf("please enter action\n1 enter client data:\n2 enter transaction data:\n3 update credit limit\n");
	while (scanf("%d", &choice) != EOF) {
		switch (choice) {
		ADD_CLIENT_DATA:
			pointer_to_file_record = fopen("record.dat", "r+");
			if (pointer_to_file_record == NULL) {
				puts("Acess denied");
			} else {
				add_client_data(pointer_to_file_record, client_data);
			}
			fclose(record.dat)
			break;
		ADD_TRANSACTION_DATA:
			pointer_to_file_transaction = fopen("transaction.dat", "r+");
			if (pointer_to_file_transaction == NULL) {
				puts("Acess denied");
			} else {
				add_transaction_data(pointer_to_file_transaction, transfer);
			}
			fclose(pointer_to_file_transaction);
			break;
		UPDATE_CREDIT_LIMIT:
			pointer_to_file_record = fopen("record.dat", "r");
			pointer_to_file_transaction = fopen("transaction.dat", "r");
			pointer_to_file_blackrecord = fopen("blackrecord.dat", "w");
		    if (pointer_to_file_record == NULL || pointer_to_file_transaction == NULL || pointer_to_file_blackrecord == NULL) {
				puts("Acess denied");
			} else {
				update_credit_limit(pointer_to_file_record, pointer_to_file_transaction, pointer_to_file_blackrecord, client_data, transfer);
			}
			fclose(pointer_to_file_record);
			fclose(pointer_to_file_transaction);
			fclose(pointer_to_file_blackrecord);
			break;
		default:	
			puts("Wrong action number");
			break;
		}
		printf("please enter action\n1 enter client data:\n2 enter transaction data:\n3 update credit limit\n");
	}
    return 0;
}
