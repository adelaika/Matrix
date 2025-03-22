S21_MATRIX = s21_matrix.a
TEST = tests/tests.c
CC = gcc
SRCS = $(wildcard s21_*.c)
GCNO = test.out-s21_*.gcno
CLEANER = rm -f test.out *.gcno *.gcov *.gcda *.info *.o
CFLAGS = -Wall -Werror -c -std=c11 -Wextra -pedantic
GCOVFLAGS = --coverage

OS := $(shell uname -s)
ifeq ($(OS), Linux)
LDFLAGS = -lcheck -lm -lsubunit
endif
ifeq ($(OS), Darwin)
LDFLAGS = -lcheck -lm
endif

.PHONY: all clean test gcov_report

all: $(S21_MATRIX)

$(S21_MATRIX): 
	$(CC) $(CFLAGS) $(SRCS)
	ar rc $(S21_MATRIX) s21_*.o
	ranlib $(S21_MATRIX)
	

test: $(TEST) $(S21_MATRIX)
	$(CC) $(TEST) $(S21_MATRIX) $(LDFLAGS) -o $@
	./test
	$(CLEANER)
	
gcov_report: $(SRCS)
	$(CC) $(GCOVFLAGS) $(SRCS) $(TEST) -o test.out $(LDFLAGS)
	./test.out
	gcov $(GCNO)
	lcov -t "report" -c -d . -o gcov_report.info
	genhtml -o ./report gcov_report.info
	open ./report/index.html
	$(CLEANER)

clean:
	rm -f test.out *.gcno *.gcov *.gcda *.info *.o test *.a
	rm -rf tests/*.log report

rebuild: clean all
