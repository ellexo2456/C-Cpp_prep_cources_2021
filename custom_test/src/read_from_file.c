#include <stdio.h>
#include <struct_data.h>
#include "read_from_file.h"
#define CASE_RECORD case 1
#define CASE_TRANSACTION case 2
#define CASE_BLACKRECORD case 3

void read_from_file(FILE *chosen_file, data *chosen_got_data, int choice) {
    switch (choice) {
    CASE_RECORD:
        fscanf(chosen_file, "%d%20s%20s%30s%16s%lf%lf%lf",
							&chosen_got_data->number,
							chosen_got_data->name,
							chosen_got_data->surname,
							chosen_got_data->addres,
							chosen_got_data->telephone_number,
							&chosen_got_data->indebtedness,
							&chosen_got_data->credit_limit,
							&chosen_got_data->cash_payments);
        break;
    CASE_TRANSACTION:
        fscanf(chosen_file, "%d %lf", &chosen_got_data->number, &chosen_got_data->cash_payments);
        break;
    CASE_BLACKRECORD:
        fscanf(chosen_file, "%d%20s%20s%30s%16s%lf%lf%lf",
							&chosen_got_data->number,
							chosen_got_data->name,
							chosen_got_data->surname,
							chosen_got_data->addres,
							chosen_got_data->telephone_number,
							&chosen_got_data->indebtedness,
							&chosen_got_data->credit_limit,
							&chosen_got_data->cash_payments);
        break;
    }
}
