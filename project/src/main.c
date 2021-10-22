#include <stdio.h>
#include "master_write.h"
#include "transaction_write.h"
#include "update_black_record.h"
#include "struct_data.h"

int main(void) {
	int choice = 0;
	FILE *ptr;
	FILE *ptr_2;
	FILE *blackrecord;
	data client_data = {0, "Client name", "Client surname", "Client adress", "Client t number", 0, 0, 0};
	data transfer = {0};
	printf("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	while (scanf("%d", &choice) != -1) {
		switch (choice) {
		case 1:                                          // Ввод данных пользователя
			ptr = fopen("record.dat", "w+");
			if (ptr == NULL) {
				puts("Not acess");
			} else {
				master_write(ptr, client_data);
				fclose(ptr);
			}
			break;
		case 2:											// Ввод данных о платежах
			ptr = fopen("transaction.dat", "w+");
			if (ptr == NULL) {
				puts("Not acess");
			} else {
				transaction_write(ptr, transfer);
				fclose(ptr);
			}
			break;
		case 3:											// Обновление данных о кредите
			ptr = fopen("record.dat", "r");
			ptr_2 = fopen("transaction.dat", "r");
			blackrecord = fopen("blackrecord.dat", "w");
		    if (ptr == NULL || ptr_2 == NULL || blackrecord == NULL) {
				puts("exit");
			} else {
				update_black_record(ptr, ptr_2, blackrecord, client_data, transfer);
				fclose(ptr);
				fclose(ptr_2);
				fclose(blackrecord);
			}
				break;
		default:
			puts("error");
			break;
		}
		printf("please enter action\n1 enter data client:\n2 enter data transaction:\n3 update base\n");
	}
    return 0;
}
