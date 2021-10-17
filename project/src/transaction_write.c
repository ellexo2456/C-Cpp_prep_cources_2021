#include <stdio.h>
#include "transaction_write.h"
#include "struct_data.h"

void transaction_write (FILE *of_ptr, data transfer) {
	int exit = 1;
	printf ("%s\n%s\n",  
		"1 Number account: ",
		"2 Client cash payments: ");
		while ((exit != 0) && (scanf("%d %lf", &transfer.number, &transfer.cash_payments) != -1)) {
			fprintf(of_ptr, "%-3d%-6.2f\n", transfer.number, transfer.cash_payments);
			printf("Exit?(0)");
			scanf("%i", &exit);
			printf("%s\n%s\n",  
					"1 Number account:",
					"2 Client cash payments: ");
		} 
}