#include <stdio.h>
#include <errno.h>
#include "s21_cat.h"

int cat_main(int argc, char *argv[]);
int cat_read_from_file(FILE *to_read, unsigned short format_info, unsigned long *current_line);
//  int cat_read_from_file_unbuffered(FILE *to_read, unsigned short format_info);
int cat_iterate_the_buffer(unsigned char *buffer_iter, unsigned long buffer_length,
                           unsigned short format_info, unsigned long *current_line);

const char s21_cat_specials_list[] = S21_CAT_SPECIAL_LIST;

int main(int argc, char *argv[]) {
    int exit_code = cat_main(argc, argv);
    return exit_code;
}

int cat_main(int argc, char *argv[]) {
    int exit_code = 0;
    unsigned char still_on_flags = 1;
    unsigned short format_info = 0;
    unsigned long current_line = 0;
    int iter = 1;
    while ((iter < argc) && (!exit_code)) {
        //  Checking flags
        if (still_on_flags) {
            if (*argv[iter] == S21_CAT_FLAG_CHECK) {
                char *arg_iter = argv[iter] + 1;
                while (*arg_iter) {
                    switch (*arg_iter) {
                    //  Common:
                        case S21_CAT_FLAG_NUMERATE:
                            format_info |= S21_CAT_FORMAT_SET_NUMERATE_NONBLANK;
                            break;
                        case S21_CAT_FLAG_NUMERATE_BLANK:
                            //  format_info |= S21_CAT_FORMAT_SET_NUMERATE_NONBLANK;    //  Not how expected
                            format_info |= S21_CAT_FORMAT_SET_NUMERATE_BLANK;
                            break;
                        case S21_CAT_FLAG_SQUEEZE:
                            format_info |= S21_CAT_FORMAT_SET_SQUEEZE;
                            break;
                        case S21_CAT_FLAG_NONPRINTING:
                            format_info |= S21_CAT_FORMAT_SET_NONPRINTING;
                            break;
                        case S21_CAT_FLAG_NONPRINTING_END:
                            format_info |= S21_CAT_FORMAT_SET_NONPRINTING;
                            format_info |= S21_CAT_FORMAT_SET_END;
                            break;
                        case S21_CAT_FLAG_NONPRINTING_TAB:
                            format_info |= S21_CAT_FORMAT_SET_NONPRINTING;
                            format_info |= S21_CAT_FORMAT_SET_TAB;
                            break;
                        case S21_CAT_FLAG_BUFFERING_DISABLE:
                            format_info |= S21_CAT_FORMAT_BUFFERING_DISABLE;
                            break;
                            //  Linux:
                        case S21_CAT_FLAG_END:
                            format_info |= S21_CAT_FORMAT_SET_END;
                            break;
                        case S21_CAT_FLAG_TAB:
                            format_info |= S21_CAT_FORMAT_SET_TAB;
                            break;
                        case S21_CAT_FLAG_ALL:
                            format_info |= S21_CAT_FORMAT_SET_NONPRINTING;
                            format_info |= S21_CAT_FORMAT_SET_END;
                            format_info |= S21_CAT_FORMAT_SET_TAB;
                            break;
                        default:
                            exit_code = S21_CAT_ERROR_OPTION_ILLEGAL;
                            S21_CAT_MESSAGE_OPTION_ILLEGAL(*arg_iter)
                            break;
                    }
                    if (exit_code)
                        break;
                    arg_iter++;
                }
                //  Fix for b+n
                if (format_info & S21_CAT_FORMAT_SET_NUMERATE_BLANK) {
                    if (format_info & S21_CAT_FORMAT_SET_NUMERATE_NONBLANK)
                        format_info &= (~S21_CAT_FORMAT_SET_NUMERATE_BLANK);
                    else
                        format_info |= S21_CAT_FORMAT_SET_NUMERATE_NONBLANK;
                }
            } else {
                still_on_flags = 0;
            }
        }
        if (!still_on_flags) {
            FILE *to_read;
            current_line = 0;
            if ((to_read = fopen(argv[iter], "r+"))) {
                cat_read_from_file(to_read, format_info, &current_line);
                fclose(to_read);
            } else {
                if (errno == ENOENT) {
                    exit_code = S21_CAT_ERROR_FILE_ABSENT;
                    S21_CAT_MESSAGE_FILE_ABSENT(argv[iter]);
                } else {
                    exit_code = S21_CAT_ERROR_FILE_IS_DIR;
                    S21_CAT_MESSAGE_FILE_IS_DIR(argv[iter]);
                }
                break;
            }
        }
        iter++;
    }
    if (!exit_code && !current_line)
        cat_read_from_file(stdin, format_info, &current_line);
    return exit_code;
}

int cat_read_from_file(FILE *to_read, unsigned short format_info, unsigned long *current_line) {
    unsigned char buffer[4096];
    unsigned long buffer_length;
    if (to_read == stdin) {
        while (fgets((char *)buffer, 4096, to_read)) {
            buffer_length = 0;
            unsigned char *buffer_iter = &(buffer[0]);
            for (; *buffer_iter; buffer_iter++)
                buffer_length++;
            cat_iterate_the_buffer(&(buffer[0]), buffer_length, format_info, current_line);
        }
    } else {
        while ((buffer_length = fread(buffer, sizeof(unsigned char), 4096, to_read))) {
            // printf("%s\n", buffer);
            cat_iterate_the_buffer(&(buffer[0]), buffer_length, format_info, current_line);
        }
    }
    return 0;
}

int cat_iterate_the_buffer(unsigned char *buffer, unsigned long buffer_length,
                           unsigned short format_info, unsigned long *current_line) {
    int exit_code = 0;

    unsigned char *buffer_iter = buffer;
    static unsigned char is_new_line = 0;
    static unsigned char is_blank = 1;

    if (!(*current_line)) {
        *current_line = 1;
        is_new_line = 1;
    }

    while (buffer_length--) {
        if (*buffer_iter == '\n') {
            is_new_line = 1;
            if (is_blank) {
                if ((is_blank == 1) || !(format_info & S21_CAT_FORMAT_SET_SQUEEZE)) {
                    if (format_info & S21_CAT_FORMAT_SET_NUMERATE_BLANK) {
                        S21_CAT_NUMERATE_LINE(*current_line);
                        (*current_line)++;
                    }
                    if (format_info & S21_CAT_FORMAT_SET_END)
                        printf("$");
                    printf("\n");
                }
            } else {
                if (format_info & S21_CAT_FORMAT_SET_END)
                    printf("$");
                printf("\n");
            }
            is_blank++;
        } else {
            is_blank = 0;
            if (is_new_line) {
                if (format_info & S21_CAT_FORMAT_SET_NUMERATE_NONBLANK) {
                    S21_CAT_NUMERATE_LINE(*current_line);
                    (*current_line)++;
                }
                is_new_line = 0;
            }
            if (*buffer_iter == '\t') {
                if (format_info & S21_CAT_FORMAT_SET_TAB)
                    printf("^I");
                else
                    printf("\t");
            } else if (((*buffer_iter >= 32) && (*buffer_iter <= 126)) ||
                       (*buffer_iter >= 160)) {
                printf("%c", *buffer_iter);
            } else if ((format_info & S21_CAT_FORMAT_SET_NONPRINTING)) {
                if (*buffer_iter <= 31)
                    printf("^%c", s21_cat_specials_list[*buffer_iter]);
                else if (*buffer_iter == 127)
                    printf("^%c", S21_CAT_SPECIAL_DEL);
                else if (*buffer_iter >= 128)
                    printf("M-^%c", s21_cat_specials_list[*buffer_iter - 128]);
            }
        }
        buffer_iter++;
    }
    return exit_code;
}
