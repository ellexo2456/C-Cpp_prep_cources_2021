#include <stdio.h>
#include "add_client_data.h"
#include "add_transaction_data.h"
#include "update_credit_limit.h"
#include "struct_data.h"
#define ADD_CLIENT_DATA 1
#define ADD_TRANSACTION_DATA 2
#define UPDATE_CREDIT_LIMIT 3

int main(void) {
	int choice = 0;
	FILE *record;
	FILE *transaction;
	FILE *blackrecord;
	data client_data = { .number = 0,
		.name = "Client name",
		.surname = "Client surname",
		.addres = "Client adress",
		.telephone_number = "Client t number",
		.indebtedness = 0,
		.credit_limit = 0,
		.cash_payments = 0
	};
	data transfer = {.number = 0,
		.cash_payments = 0
	};
	printf("please enter action\n1 enter client data:\n2 enter transaction data:\n3 update credit limit\n");
	while (scanf("%d", &choice) != EOF) {
		switch (choice) {
		case ADD_CLIENT_DATA:
			record = fopen("record.dat", "r+");
			if (record == NULL) {
				puts("Acess denied");
			} else {
				add_client_data(record, client_data);
				fclose(record);
			}
			break;
		case ADD_TRANSACTION_DATA:
			transaction = fopen("transaction.dat", "r+");
			if (transaction == NULL) {
				puts("Acess denied");
			} else {
				add_transaction_data(transaction, transfer);
				fclose(transaction);
			}
			break;
		case UPDATE_CREDIT_LIMIT:
			record = fopen("record.dat", "r");
			transaction = fopen("transaction.dat", "r");
			blackrecord = fopen("blackrecord.dat", "w");
		    if (record == NULL || transaction == NULL || blackrecord == NULL) {
				puts("Acess denied");
			} else {
				update_credit_limit(record, transaction, blackrecord, client_data, transfer);
				fclose(record);
				fclose(transaction);
				fclose(blackrecord);
			}
			break;
		default:
			puts("Wrong action number");
			break;
		}
		printf("please enter action\n1 enter client data:\n2 enter transaction data:\n3 update credit limit\n");
	}
    return 0;
}
