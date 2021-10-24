#ifndef PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
#define PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
#include <stdio.h>
#include "struct_data.h"

void update_credit_limit(FILE *record, FILE *transaction, FILE *blackrecord, data client_data, data transfer);

#endif  // PROJECT_INCLUDE_UPDATE_CREDIT_LIMIT_H_
