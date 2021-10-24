#include <stdio.h>
#include "add_transaction_data.h"
#include "struct_data.h"

void add_transaction_data(FILE *transaction, data transfer) {
	printf("%s\n%s\n",
		"1 Number account: ",
		"2 Client cash payments: ");
		while ((scanf("%d %lf", &transfer.number, &transfer.cash_payments) != EOF)) {  // Ввод данных
			fprintf(transaction, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);  // Запись данных в файл
			printf("%s\n%s\n",
					"1 Number account:",
					"2 Client cash payments: ");
		}
}
