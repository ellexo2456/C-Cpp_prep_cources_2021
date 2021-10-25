#ifndef PROJECT_INCLUDE_STRUCT_DATA_H_
#define PROJECT_INCLUDE_STRUCT_DATA_H_

typedef struct {
	int number;
	char name[20];
	char surname[20];
	char addres[30];
	char telephone_number[15];
	double indebtedness;
	double credit_limit;
	double cash_payments;
	} data;

#endif  // PROJECT_INCLUDE_STRUCT_DATA_H_
#include "data_compare.h"
#include <stdio.h>
#include <string.h>

void data_compare(data chosen_expected_data, data chosen_got_data, int choice) {
    int false = 0;
    switch (false) {
    case chosen_expected_data.number == chosen_got_data.number:
        puts("File record: number test failed");
        break;
    case choice+(!strncmp(chosen_expected_data.name, chosen_got_data.name, 25)):
        puts("File record: name test failed");
        break;
    case choice+(!strncmp(chosen_expected_data.surname, chosen_got_data.surname, 25)):
        puts("File record: surname test failed");
        break;
    case choice+(!strncmp(chosen_expected_data.telephone_number, chosen_got_data.telephone_number, 20)):
        puts("File record: telephone_number test failed");
        break;
    case choice+(!strncmp(chosen_expected_data.addres, chosen_got_data.addres, 35)):
        puts("File record: addres test failed");
        break;
    case choice+(chosen_expected_data.indebtedness == chosen_got_data.indebtedness):
        puts("File record: indebtedness test failed");
        break;
    case choice+(chosen_expected_data.credit_limit == chosen_got_data.credit_limit):
        puts("File record: credit_limit test failed");
        break;
    case chosen_expected_data.cash_payments == chosen_got_data.cash_payments:
        puts("File record: cash_payments test failed");
        break;
    default:
        puts("ALL TESTS SUCCEED");
    }
}