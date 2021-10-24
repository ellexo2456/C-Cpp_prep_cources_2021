#include <stdio.h>
#include <struct_data.h>
#include "write_to_file.h"
#define CASE_RECORD case 1
#define CASE_TRANSACTION case 2
#define CASE_BLACKRECORD case 3

void write_to_file(FILE *chosen_file, data chosen_expected_data, int choice) {
    switch (choice) {
    CASE_RECORD:
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
    CASE_TRANSACTION:
        fprintf(chosen_file, "%-3d%-6.2f\n", chosen_expected_data.number, chosen_expected_data.cash_payments);
        break;
    CASE_BLACKRECORD:
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
    }
}
