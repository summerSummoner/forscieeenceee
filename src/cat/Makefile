WFLAGS = -std=c11 -Wall -Werror -Wextra #-D_GNU_SOURCE -Ofast
TESTRUN = ./s21_cat -vetsbn checkfile

# ------------- MAIN ------------- #

all: clean s21_cat clear

rebuild: clean all

clean:
	rm -rf *.o *.gch
	rm -rf s21_cat
# *.a ./gcov_report *.gcda *.gcno coverage.info

clear:
	rm -rf *.o *.gch

# ------------- BUILD ------------- #

s21_cat.o:
	gcc -c s21_cat.c s21_cat.h ${WFLAGS}

s21_cat: s21_cat.o
	gcc -o s21_cat s21_cat.o ${WFLAGS}

# ------------- TESTS ------------- #

# --- Test --- #

test:
	@echo "\n# -------------- CAT -------------- #"
	cat -vetsbn checkfile
	@echo "\n\n# ------------ S21_CAT ------------ #"
	${TESTRUN}

# --- Style --- #

style:
	cp ../../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../../materials/linters/cpplint.py --extension=c *.c *.h
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

# --- Leaks --- #

valgrind:
	valgrind --log-file="valres.txt" --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --leak-resolution=med -s ./s21_cat

leaks:
	CK_FORK=no leaks --atExit -- ${TESTRUN}