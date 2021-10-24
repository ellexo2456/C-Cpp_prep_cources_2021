#include <stdio.h>
#include <struct_data.h>

write_to_file(FILE *pointer_to_chosen_file, data chosen_expected_data, choice) {
    switch (choice) {
    case 1:
        fprintf(pointer_to_chosen_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
							chosen_expected_data.number,
							chosen_expected_data.name,
							chosen_expected_data.surname,
							chosen_expected_data.addres,
							chosen_expected_data.tel_number,
							chosen_expected_data.indebtedness,
							chosen_expected_data.credit_limit,
							chosen_expected_data.cash_payments);
        break;
    case 2:
        fprintf(pointer_to_chosen_file, "%-3d%-6.2f\n", chosen_expected_data.number, chosen_expected_data.cash_payments);
        break;
    case 3:
        fprintf(pointer_to_chosen_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
                                chosen_expected_data.number,
                                chosen_expected_data.name,
                                chosen_expected_data.surname,
                                chosen_expected_data.addres,
                                chosen_expected_data.tel_number,
                                chosen_expected_data.indebtedness,
                                chosen_expected_data.credit_limit,
                                chosen_expected_data.cash_payments);
        break;
    }
}
