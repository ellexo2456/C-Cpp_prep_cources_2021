#ifndef PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
#define PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
#include <stdio.h>
#include "struct_data.h"

void update_credit_limit(FILE *pointer_to_file_record, FILE *pointer_to_file_transaction, FILE *pointer_to_file_blackrecord, data client_data, data transfer);

#endif  // PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
