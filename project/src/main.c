#include <stdio.h>
#include "master_write.h"
#include "transaction_write.h"
#include "update_black_record.h"
#include "struct_data.h"
#include "data_write_read_test.h"

int main(void) {
	printf("Start the data write/read test");
	data_write_read_test();
	int choice = 0;	
	FILE *ptr, *ptr_2 , *blackrecord;
	data client_data, transfer;
	printf ("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	while (scanf("%d", &choice) != -1) {
		switch (choice) {
		case 1:
			ptr = fopen ("record.dat", "r+");
			if (ptr == NULL) {
				puts ("Not acess");	
			} else {
				master_write (ptr, client_data);	
				fclose (ptr);
			}
			break;
		case 2:
			ptr = fopen ("transaction.dat", "r+");
			if (ptr == NULL) {
				puts ("Not acess");	
			} else {
				transaction_write (ptr, transfer);
				fclose (ptr);
			}
			break;	
		case 3:
			ptr = fopen ("record.dat", "r");
			ptr_2 = fopen ("transaction.dat", "r");
			blackrecord = fopen ("blackrecord.dat", "w");	
		    if (ptr == NULL || ptr_2 == NULL || blackrecord == NULL) {
				puts("exit");
			} else {
				update_black_record (ptr, ptr_2, blackrecord, client_data, transfer);
				ptr = fopen ("record.dat", "w");
				fclose (ptr);
				fclose (ptr_2);	
				fclose (blackrecord);
			}
				break;
			default:
				puts ("error");
				break ;
		}
 	printf ("%s", "please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	}
    return 0;
}
