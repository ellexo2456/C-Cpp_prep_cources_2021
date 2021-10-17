#include <stdio.h>
#include "update_black_record.h"
#include "struct_data.h"

void update_black_record (FILE *of_ptr, FILE *of_ptr_2, FILE *blackrecord, data client_data, data transfer) {
	while (fscanf(of_ptr, "%d%s%s%s%s%lf%lf%lf", &client_data.number, client_data.name, client_data.surname, client_data.addres, client_data.tel_number, &client_data.indebtedness, &client_data.credit_limit, &client_data.cash_payments) != -1) {  // Поиск информации об одном 
		while (fscanf(of_ptr_2, "%d %lf",  &transfer.number , &transfer.cash_payments) != -1) {																																						// пользователе в двух файлах.					
			if (client_data.number == transfer.number && transfer.cash_payments != 0) {																																								// В случае успеха - обновление информации
				client_data.credit_limit += transfer.cash_payments;																																													// о кредите. Иначе - поиск информации о следующем пользователе
			} 
		}
		fprintf (blackrecord,"%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client_data.number, client_data.name, client_data.surname, client_data.addres, client_data.tel_number, client_data.indebtedness, client_data.credit_limit, client_data.cash_payments);  // Запись обновлённых данных в отдельный файл
		rewind (of_ptr_2);
	} 
}