#ifndef SRC_GREP_S21_GREP_H_
#define SRC_GREP_S21_GREP_H_

//  ----------------------------------------------------------------------------------------
//                                          FLAGS
//  ----------------------------------------------------------------------------------------

#ifndef _S21_GREP_FORMAT
#define _S21_GREP_FORMAT

#define S21_GREP_FLAG_CHECK             '-'     //  Flag look-for symbol

#define S21_GREP_FORMAT_PATTERN         'e'     //  Pattern.
#define S21_GREP_FORMAT_NOCASE          'i'     //  Ignore uppercase vs. lowercase.
#define S21_GREP_FORMAT_INVERT          'v'     //  Invert match.
#define S21_GREP_FORMAT_LINES           'c'     //  Output count of matching lines only.
#define S21_GREP_FORMAT_FILES           'l'     //  Output matching files only.
#define S21_GREP_FORMAT_NUMERATE        'n'     //  Precede each matching line with a line number.
#define S21_GREP_FORMAT_LINES_NONAME    'h'     //  Output matching lines without preceding them
                                                //  by file names.
#define S21_GREP_FORMAT_SUPPRESS        's'     //  Suppress error messages about nonexistent or
                                                //  unreadable files.
#define S21_GREP_FORMAT_FROMFILE        'f'     //  Take regexes from a file.
#define S21_GREP_FORMAT_PARTIAL         'o'     //  Output the matched parts of a matching line.

#define S21_GREP_FORMAT_SET_PATTERN         1
#define S21_GREP_FORMAT_SET_NOCASE          2
#define S21_GREP_FORMAT_SET_INVERT          4
#define S21_GREP_FORMAT_SET_LINES           8
#define S21_GREP_FORMAT_SET_FILES           16
#define S21_GREP_FORMAT_SET_NUMERATE        32
#define S21_GREP_FORMAT_SET_LINES_NONAME    64
#define S21_GREP_FORMAT_SET_SUPPRESS        128
#define S21_GREP_FORMAT_SET_FROMFILE        256
#define S21_GREP_FORMAT_SET_PARTIAL         512

#endif  // _S21_GREP_FORMAT

//  ----------------------------------------------------------------------------------------
//                                         MACRO
//  ----------------------------------------------------------------------------------------

#ifndef _S21_GREP_MESSAGES
#define _S21_GREP_MESSAGES

#define S21_GREP_MESSAGE_ERROR {\
    printf("usage: grep [-abcDEFGHhIiJLlmnOoqRSsUVvwxZ] [-A num] [-B num] [-C[num]]\n");\
    printf("\t[-e pattern] [-f file] [--binary-files=value] [--color=when]\n");\
    printf("\t[--context[=num]] [--directories=action] [--label] [--line-buffered]\n");\
    printf("\t[--null] [pattern] [file ...]\n");\
}

#define S21_GREP_MESSAGE_FILE_ABSENT(PATH)                  \
        printf("grep: %s: No such file or directory\n", PATH)

#define S21_GREP_MESSAGE_FILE_IS_DIR(PATH)                  \
        printf("grep: %s: Is a directory\n", PATH)

#endif  // _S21_GREP_MESSAGES

//  ----------------------------------------------------------------------------------------
//                                         ERRORS
//  ----------------------------------------------------------------------------------------

#ifndef _S21_GREP_ERRORS
#define _S21_GREP_ERRORS

#define S21_GREP_ERROR_NO_ARGS          1
#define S21_GREP_ERROR_OPTION_ILLEGAL   1
#define S21_GREP_ERROR_FILE_ABSENT      1
#define S21_GREP_ERROR_FILE_IS_DIR      1

#endif  // _S21_GREP_ERRORS

#endif  // SRC_GREP_S21_GREP_H_

