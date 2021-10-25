#!/usr/bin/env bash

PROG_PATH=./main.out
ROOT=$(dirname $(realpath $0))

RECORDS_F_NAME="record.dat"
TRANSACTIONS_F_NAME="transaction.dat"
BLACKRECORDS_F_NAME="blackrecord.dat"

rm -f $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME
touch $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME

IN="1
1
Alena
Lebedeva
tst_address_1
tst_tel_1
11
10
220
2
Artur
King
tst_address_2
tst_tel_2
100
200
10000"

echo "${IN}" | eval "${PROG_PATH}"

IN="2
1
80
2
30000"

echo "${IN}" | eval "${PROG_PATH}"

IN="3"

echo "${IN}" | eval "${PROG_PATH}"

for file in $RECORDS_F_NAME $TRANSACTIONS_F_NAME $BLACKRECORDS_F_NAME; do
	diff $file $ROOT/"custom_"${file}.gold
	if [[ "$?" != "0" ]]; then
		echo "Files mismatches"
		exit 1
	fi
done

echo "***** TEST SUCCEED *****"
