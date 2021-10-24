#include <stdio.h>
#include "add_client_data.h"
#include "struct_data.h"

void add_client_data(FILE *record, data client) {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: ");
	while (1) {
		if (scanf("%d%20s%20s%30s",  // Ввод данных пользователя
					&client.number,
					client.name,
					client.surname,
					client.addres) != EOF)
			fprintf(record, "%-12d%-11s%-11s%-16s",  // Запись данных пользователя в файл
								client.number,
								client.name,
								client.surname,
								client.addres);
		else
			break;
		if (scanf("%15s%lf%lf%lf",  // Ввод данных пользователя
					client.telephone_number,
					&client.indebtedness,
					&client.credit_limit,
					&client.cash_payments) != EOF)
			fprintf(record, "%20s%12.2f%12.2f%12.2f\n",  // Запись данных пользователя в файл
					client.telephone_number,
					client.indebtedness,
					client.credit_limit,
					client.cash_payments);
		else
			break;
		printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"9 Client cash payments: ");
	}
}
