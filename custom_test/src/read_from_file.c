#include <stdio.h>
#include <struct_data.h>
#include "read_from_file.h"
#define RECORD_OR_BLACKRECORD 1
#define TRANSACTION 2

void read_from_file(FILE *chosen_file, data *chosen_got_data, int choice) {
    switch (choice) {
    case RECORD_OR_BLACKRECORD:
		fscanf(chosen_file, "%d%20s%20s%30s",
				&chosen_got_data->number,
				chosen_got_data->name,
				chosen_got_data->surname,
				chosen_got_data->addres);
		fscanf(chosen_file, "%16s%lf%lf%lf",
				chosen_got_data->telephone_number,
				&chosen_got_data->indebtedness,
				&chosen_got_data->credit_limit,
				&chosen_got_data->cash_payments);
		break;	
    case TRANSACTION:
        fscanf(chosen_file, "%d %lf", &chosen_got_data->number, &chosen_got_data->cash_payments);
        break;
	}
}