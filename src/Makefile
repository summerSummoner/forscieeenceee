TARGET=s21_matrix
CC=gcc
CFLAGS=-Wall -Wextra -Werror -std=c11 -g
OBJECTS=$(TARGET).o

all: clean test

# s21_matrix.a
$(TARGET).a: $(OBJECTS)
	ar rcs $@ $^
	ranlib $@
	cp $@ lib$@

# s21_matrix.o
$(TARGET).o: $(TARGET).c $(TARGET).h
	$(CC) $(CFLAGS) -c -o $@ $<

test.o: tests.c
	$(CC) $(CFLAGS) -c -o $@ $<

test: test.o $(TARGET).a
	$(CC) $(CFLAGS) $^ -lcheck -lm -o $@
	./$@

gcov_report:
	$(CC) --coverage tests.c -o s21_test $(TARGET).c  -lcheck
	./s21_test
	lcov -t "s21_test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open report/index.html

check: cpplint cppcheck leaks
cpplint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h
leaks:
	CK_FORK=no leaks --atExit -- ./test

clean:
	rm -f *.o test *.a
	rm -rf *.gcno *.gcda s21_test *.info
	rm -rf report
	rm -rf *.cfg
