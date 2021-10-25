TARGET = ./main.out
HDRS_DIR = project/include

SRCS = \
	project/src/main.c \
	project/src/add_client_data.c \
	project/src/add_transaction_data.c \
	project/src/update_credit_limit.c 
	
.PHONY: all build rebuild check test memtest clean sh_custom_test

all: clean check test memtest

$(TARGET): $(SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(HDRS_DIR) -o $(TARGET) $(CFLAGS) $(SRCS)

build: $(TARGET)

rebuild: clean build

check:
	./linters/run.sh

test: $(TARGET)
	./btests/run.sh $(TARGET)

memtest: $(TARGET)
	./btests/run.sh $(TARGET) --memcheck

clean:
	rm -rf $(TARGET)

#Тестирующий модуль через .sh

sh_custom_test: $(TARGET)
	./btests/custom_tests/custom_run.sh

#Тестирующий модуль через функции

TEST_TARGET = ./test_main.out
TEST_HDRS_DIR = custom_test/include

TEST_SRCS = \
	custom_test/src/main.c \
	custom_test/src/write_to_file.c \
	custom_test/src/read_from_file.c

.PHONY: test_clean custom_test

$(TEST_TARGET): $(TEST_SRCS) 
	$(CC) -Wpedantic -Wall -Wextra -Werror -I $(TEST_HDRS_DIR) -o $(TEST_TARGET) $(CFLAGS) $(TEST_SRCS)

custom_test: $(TEST_TARGET)
	$(TEST_TARGET)

test_clean:
	rm -rf $(TEST_TARGET)
