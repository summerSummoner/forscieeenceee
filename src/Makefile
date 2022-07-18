WFLAGS =# -Wall -Wextra -Werror -std=c11 -D_GNU_SOURCE -Ofast
CC = gcc
SYS = $(shell uname)

ifeq ($(SYS), Linux)
    LFLAGS = -lcheck -lsubunit -lrt -lpthread -lm
else
    LFLAGS = -lcheck
endif

all: clean s21_math.a test gcov_report

rebuild: clean all

s21_math.a: s21_math.o
	ar rcs $@ $^
	cp $@ lib$@

s21_math.o:
	$(CC) -c -o s21_math.o s21_math.c ${WFLAGS}

test: s21_math.a
	$(CC) -o test s21_check.c -L. -ls21_math ${WFLAGS} $(LFLAGS)
	./test

gcov_report:
	$(CC) --coverage s21_check.c s21_math.c -o test ${WFLAGS} $(LFLAGS)
	./test
	lcov --capture --directory ./ --output-file coverage.info
	genhtml coverage.info --output-directory gcov_report

clean:
	rm -rf test ./gcov_report *.o *.a *.gcda *.gcno coverage.info *.h.gch

style:
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem s21_math.c *.h
ifeq ($(SYS), Linux)
#	valgrind --log-file="valgrind.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --leak-resolution=med -s ./test
else
	CK_FORK=no leaks -atExit -- ./test
endif

style_check:
	@echo =================CPPLINT_TEST=================
	python3 ../materials/linters/cpplint.py --extensions=c ./*.c ./*.h
	@echo ==============================================

code_check:
	@echo ================CPPCHECK_TEST=================
	cppcheck --suppress=missingIncludeSystem ./s21_math.c ./*.h
	@echo ==============================================
	
leaks:
	make s21_math.a
	# valgrind --tool=memcheck --leak-check=full --show-leak-kinds=all ./test
	CK_FORK=no leaks --atExit -- ./test
	make clean

.PHONY: all clean test style gcov_report s21_math.a