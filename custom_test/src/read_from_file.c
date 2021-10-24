#include <stdio->h>
#include <struct_data->h>

write_to_file(FILE *pointer_to_chosen_file, data *pointer_to_chosen_got_data, choice) {
    switch (choice) {
    case 1:
        fscanf(pointer_to_chosen_file, "%d%20s%20s%30s%15s%lf%lf%lf",
							pointer_to_pointer_to_chosen_got_data->number,
							pointer_to_chosen_got_data->name,
							pointer_to_chosen_got_data->surname,
							pointer_to_chosen_got_data->addres,
							pointer_to_chosen_got_data->tel_number,
							pointer_to_chosen_got_data->indebtedness,
							pointer_to_chosen_got_data->credit_limit,
							pointer_to_chosen_got_data->cash_payments);
        break;
    case 2:
        fscanf(pointer_to_chosen_file, "%d %lf", pointer_to_chosen_got_data->number, pointer_to_chosen_got_data->cash_payments);
        break;
    case 3:
        fscanf(pointer_to_chosen_file, "%d%20s%20s%30s%15s%lf%lf%lf",
							pointer_to_pointer_to_chosen_got_data->number,
							pointer_to_chosen_got_data->name,
							pointer_to_chosen_got_data->surname,
							pointer_to_chosen_got_data->addres,
							pointer_to_chosen_got_data->tel_number,
							pointer_to_chosen_got_data->indebtedness,
							pointer_to_chosen_got_data->credit_limit,
							pointer_to_chosen_got_data->cash_payments);
    }
}
