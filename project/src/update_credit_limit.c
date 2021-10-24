#include <stdio.h>
#include "update_credit_limit.h"
#include "struct_data.h"

void update_credit_limit(FILE *pointer_to_file_record, FILE *pointer_to_file_transaction, FILE *pointer_to_file_blackrecord, data client_data, data transfer) {
	while (fscanf(pointer_to_file_record, "%d%20s%20s%30s%15s%lf%lf%lf",					// Поиск информации об одном
					&client_data.number,									// пользователе в двух файлах.
					client_data.name,
					client_data.surname,
					client_data.addres,
					client_data.tel_number,
					&client_data.indebtedness,
					&client_data.credit_limit,
					&client_data.cash_payments) != EOF) {
		while (fscanf(pointer_to_file_transction, "%d %lf",  &transfer.number , &transfer.cash_payments) != EOF) {
			if (client_data.number == transfer.number && transfer.cash_payments != 0) {  // В случае успеха -
				client_data.credit_limit += transfer.cash_payments;			// обновление информации о кредите.
			}																// Иначе - поиск информации о следующем пользователе
		}
		fprintf(pointer_to_file_blackrecord, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
								client_data.number,
								client_data.name,
								client_data.surname,
								client_data.addres,
								client_data.tel_number,
								client_data.indebtedness,
								client_data.credit_limit,
								client_data.cash_payments);  // Запись обновлённых данных в отдельный файл
		rewind(pointer_to_file_transction);
	}
}
