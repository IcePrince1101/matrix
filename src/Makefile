CC=gcc
CC_FLAGS=-g -Wall -Werror -Wextra -std=c11 
#-fsanitize=address
test_flags=-fprofile-arcs -ftest-coverage
OS=$(shell uname -s)
VALGRIND_FLAGS = --log-file="valgrind.txt" --track-origins=yes --trace-children=yes --leak-check=full --leak-resolution=med

ifeq ($(OS),Linux)
	test_libs=-lcheck -lm -lsubunit
	open=xdg-open
else
	test_libs=-lcheck
	open=open
endif

all: clean clang s21_matrix.a gcov_report

s21_matrix.a:
	$(CC) $(CC_FLAGS) -c *.c
	ar rc s21_matrix.a *.o
	ranlib s21_matrix.a
	rm -f *.o

test:clean
	$(CC) $(CC_FLAGS) $(test_flags) *.c tests/*.c -o test $(test_libs)
	./test
	mv *.gcda *.gcno tests/

gcov_report: test
	lcov -t "test" -o $(tests_info)test.info -c -d .
	genhtml -o report $(tests_info)test.info
	$(open) report/index.html

clean:
	rm -f tests/*.gcda tests/*.gcno *.gcda *.gcno *.txt
	rm -f test
	rm -f *.o
	rm -f s21_matrix.a
	rm -rf report

clang:
	cp ../materials/linters/.clang-format .
	clang-format -n *.h *.c */*.c */*.h
	rm -f .clang-format

clang-format:
	cp ../materials/linters/.clang-format .
	clang-format -i *.h *.c */*.c */*.h
	rm -f .clang-format