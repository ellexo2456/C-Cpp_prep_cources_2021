#include <stdio.h>
#include "master_write.h"
#include "struct_data.h"

void master_write(FILE *of_ptr , data client) {
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
					client.tel_number,
					&client.indebtedness,
					&client.credit_limit,
					&client.cash_payments) != -1) {  // Ввод данных пользователя
		fprintf(of_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n",
							client.number,
							client.name,
							client.surname,
							client.addres,
							client.tel_number,
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
