#include <stdio.h>
#include <struct_data.h>
#include "read_from_file.h"

void read_from_file(FILE *chosen_file, data *chosen_got_data, int choice) {
    switch (choice) {
    case 1:
        fscanf(chosen_file, "%d%20s%20s%30s%15s%lf%lf%lf",
							chosen_got_data->number,
							chosen_got_data->name,
							chosen_got_data->surname,
							chosen_got_data->addres,
							chosen_got_data->telephone_number,
							chosen_got_data->indebtedness,
							chosen_got_data->credit_limit,
							chosen_got_data->cash_payments);
        break;
    case 2:
        fscanf(chosen_file, "%d %lf", chosen_got_data->number, chosen_got_data->cash_payments);
        break;
    case 3:
        fscanf(chosen_file, "%d%20s%20s%30s%15s%lf%lf%lf",
							chosen_got_data->number,
							chosen_got_data->name,
							chosen_got_data->surname,
							chosen_got_data->addres,
							chosen_got_data->telephone_number,
							chosen_got_data->indebtedness,
							chosen_got_data->credit_limit,
							chosen_got_data->cash_payments);
        break;
    }
}
