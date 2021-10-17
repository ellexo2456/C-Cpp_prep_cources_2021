#include <stdio.h>
#include "master_write.h"
#include "struct_data.h"

void master_write (FILE *of_ptr , data client) {
	int exit = 1;
	printf ("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",  
			"1 Number account: ",
			"2 Client name: ",
			"3 Surname: ",
			"4 Addres client: ",
			"5 Client Telnum: ",
			"6 Client indebtedness: ",
			"7 Client credit limit: ",
			"8 Client cash payments: ");
	while ((exit != 0) && (scanf ("%d%s%s%s%s%lf%lf%lf", &client.number, client.name, client.surname, client.addres, client.tel_number, &client.indebtedness, &client.credit_limit , &client.cash_payments) != -1)) {
		fprintf (of_ptr, "%-12d%-11s%-11s%-16s%20s%12.2f%12.2f%12.2f\n", client.number, client.name, client.surname, client.addres, client.tel_number, client.indebtedness, client.credit_limit , client.cash_payments);
		printf("Exit?(0)");
		scanf("%i", &exit);
		printf ("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n",  
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