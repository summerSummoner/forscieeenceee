WFLAGS = -std=c11 -Wall -Werror -Wextra #-D_GNU_SOURCE -Ofast
TESTRUN = ./s21_grep text textfile

# ------------- MAIN ------------- #

all: clean s21_grep clear

rebuild: clean all

clean:
	rm -rf *.o *.gch
	rm -rf s21_grep
# *.a ./gcov_report *.gcda *.gcno coverage.info

clear:
	rm -rf *.o *.gch

# ------------- BUILD ------------- #

s21_grep.o:
	gcc -c s21_grep.c s21_grep.h ${WFLAGS}

s21_grep: s21_grep.o
	gcc -o s21_grep s21_grep.o ${WFLAGS}

# ------------- TESTS ------------- #

# --- Test --- #

##

# --- Style --- #

style:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

# --- Leaks --- #

valgrind:
	valgrind --log-file="valres.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --leak-resolution=med -s ./s21_grep

leaks:
	CK_FORK=no leaks --atExit -- ${TESTRUN}