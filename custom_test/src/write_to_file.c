#include <stdio.h>
#include <struct_data.h>
#include "write_to_file.h"
#define RECORD_OR_BLACKRECORD 1
#define TRANSACTION 2

void write_to_file(FILE *chosen_file, data chosen_expected_data, int choice) {
    switch (choice) {
    case RECORD_OR_BLACKRECORD:
        fprintf(chosen_file, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
							chosen_expected_data.number,
							chosen_expected_data.name,
							chosen_expected_data.surname,
							chosen_expected_data.addres,
							chosen_expected_data.telephone_number,
							chosen_expected_data.indebtedness,
							chosen_expected_data.credit_limit,
							chosen_expected_data.cash_payments);
        break;
    case TRANSACTION:
        fprintf(chosen_file, "%-3d%-6.2f\n", chosen_expected_data.number, chosen_expected_data.cash_payments);
        break;
    }
}
