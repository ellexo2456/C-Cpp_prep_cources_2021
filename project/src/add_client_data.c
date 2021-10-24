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
	while (scanf("%d%20s%20s%30s%15s%lf%lf%lf",
					&client.number,
					client.name,
					client.surname,
					client.addres,
					client.telephone_number,
					&client.indebtedness,
					&client.credit_limit,
					&client.cash_payments) != EOF) {  // Ввод данных пользователя
		fprintf(record, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
							client.number,
							client.name,
							client.surname,
							client.addres,
							client.telephone_number,
							client.indebtedness,
							client.credit_limit,
							client.cash_payments);  // Запись данных пользователя в файлл
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
