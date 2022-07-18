#include <stdio.h>
#include <stdlib.h>

#include <regex.h>
#include <string.h>
#include <errno.h>

#include "s21_grep.h"

//  Some functional... functions?:
int grep_main(int argc, char *argv[]);

unsigned long get_word_length(const char *word);
// char *paste_word(const char *word, unsigned long word_length,
//                  char *where);

int grep_file_process(  // FILE *to_process,
                      char *file_name,
                      char **patterns, unsigned long patterns_count,
                      unsigned short format_info);

char **init_strings(char **strings, unsigned long strings_count);
void process_file_error(char *file_name,
                        unsigned short format_info, int *exit_code);
unsigned long you_did_it_yaaay(char *output, unsigned short format_info,
                               char *file_name, unsigned long current_line);

//  Patterns:
char **read_pattern(char *arg,
                    char **patterns, unsigned long *patterns_count,
                    int *exit_code);
char **read_patterns_from_file(char *arg,
                               char **patterns, unsigned long *patterns_count,
                               unsigned short format_info, int *exit_code);

//  Files:
// FILE **init_files(FILE **files, unsigned long files_count);
char **set_files(int argc, char *argv[], int iter,
                 char **files, unsigned long *files_count);

int main(int argc, char *argv[]) {
    int exit_code = grep_main(argc, argv);
    return exit_code;
}

int grep_main(int argc, char *argv[]) {
    int exit_code = 1;
    if (argc > 1) {
        exit_code = 0;
        unsigned short format_info = 0;

        char **patterns = NULL;
        unsigned long patterns_count = 0;

        char **files = NULL;
        unsigned long files_count = 0;

        //  Check flags first
        int iter = 1;
        while ((iter < argc) && (!exit_code)) {
            if (*argv[iter] == S21_GREP_FLAG_CHECK) {
                char *arg_iter = argv[iter] + 1;
                while (*arg_iter && !exit_code) {
                    switch (*arg_iter) {
                        //  -e %pattern%
                        case S21_GREP_FORMAT_PATTERN:
                            format_info |= S21_GREP_FORMAT_SET_PATTERN;
                            break;
                        case S21_GREP_FORMAT_NOCASE:
                            format_info |= S21_GREP_FORMAT_SET_NOCASE;
                            break;
                        case S21_GREP_FORMAT_INVERT:
                            format_info |= S21_GREP_FORMAT_SET_INVERT;
                            break;
                        case S21_GREP_FORMAT_LINES:
                            format_info |= S21_GREP_FORMAT_SET_LINES;
                            break;
                        case S21_GREP_FORMAT_FILES:
                            format_info |= S21_GREP_FORMAT_SET_FILES;
                            break;
                        case S21_GREP_FORMAT_NUMERATE:
                            format_info |= S21_GREP_FORMAT_SET_NUMERATE;
                            break;
                        case S21_GREP_FORMAT_LINES_NONAME:
                            format_info |= S21_GREP_FORMAT_SET_LINES_NONAME;
                            break;
                        case S21_GREP_FORMAT_SUPPRESS:
                            format_info |= S21_GREP_FORMAT_SET_SUPPRESS;
                            break;
                        case S21_GREP_FORMAT_FROMFILE:
                            format_info |= S21_GREP_FORMAT_SET_FROMFILE;
                            break;
                        case S21_GREP_FORMAT_PARTIAL:
                            format_info |= S21_GREP_FORMAT_SET_PARTIAL;
                            break;
                        //  Bad option:
                        default:
                            exit_code = S21_GREP_ERROR_OPTION_ILLEGAL;
                            S21_GREP_MESSAGE_ERROR;
                            break;
                    }
                    if (exit_code)
                        break;
                    arg_iter++;
                }
            }
            iter++;
        }
        //  Correct input, go on:
        if (!exit_code) {
            //  Exclude if from file:
            // if (format_info & S21_GREP_FORMAT_SET_FROMFILE)
            //     format_info &= (~S21_GREP_FORMAT_SET_PATTERN);

            //  Setup patterns:
            iter = 1;
            while ((iter < argc) && (!exit_code)) {
                if (*argv[iter] == S21_GREP_FLAG_CHECK) {
                    char *arg_iter = argv[iter] + 1;
                    if (format_info & S21_GREP_FORMAT_SET_FROMFILE) {
                        if (*arg_iter == S21_GREP_FORMAT_FROMFILE) {
                            //  If space go to next arg
                            if (*(++arg_iter) == '\0') {
                                iter++;
                                if (iter == argc) {
                                    S21_GREP_MESSAGE_ERROR;
                                    exit_code = S21_GREP_ERROR_OPTION_ILLEGAL;
                                    break;
                                }
                                arg_iter = argv[iter];
                            }
                            patterns = read_patterns_from_file(arg_iter,
                                                               patterns, &patterns_count,
                                                               format_info, &exit_code);
                            break;
                        }
                    } else if (format_info & S21_GREP_FORMAT_SET_PATTERN) {
                        if (*arg_iter == S21_GREP_FORMAT_PATTERN) {
                            //  If space go to next arg
                            if (*(++arg_iter) == '\0') {
                                iter++;
                                if (iter == argc) {
                                    if (!(format_info & S21_GREP_FORMAT_SET_SUPPRESS))
                                        S21_GREP_MESSAGE_ERROR;
                                    exit_code = S21_GREP_ERROR_OPTION_ILLEGAL;
                                    break;
                                }
                                arg_iter = argv[iter];
                            }
                            patterns = read_pattern(arg_iter, patterns, &patterns_count, &exit_code);
                        }
                    }
                } else {
                    if (!patterns_count) {
                        if (!((format_info & S21_GREP_FORMAT_SET_FROMFILE) ||
                              (format_info & S21_GREP_FORMAT_SET_PATTERN))) {
                            patterns = read_pattern(argv[iter], patterns, &patterns_count, &exit_code);
                            //  Get out of here!
                            iter++;
                            break;
                        }
                    }
                }
                iter++;
            }

            //  Setup iterator:
            if ((format_info & S21_GREP_FORMAT_SET_FROMFILE) ||
                (format_info & S21_GREP_FORMAT_SET_PATTERN))
                iter = 1;
            //  Setup files:
            files = set_files(argc, argv, iter, files, &files_count);

            // printf("%lu\n", files_count);
            // for (unsigned long temp = 0; temp < files_count; temp++)
            //     printf("%s\n", files[temp]);

            // FILE *to_check;
            if (files_count <= 1)
                format_info |= S21_GREP_FORMAT_SET_LINES_NONAME;
            if (files_count) {
                /*
                for (unsigned long temp = 0; temp < files_count; temp++) {
                    if ((to_check = fopen(files[temp], "r+"))) {
                        grep_file_process(to_check, patterns, patterns_count, format_info);
                        fclose(to_check);
                    } else {
                        process_file_error(files[temp], format_info, &exit_code);
                    }
                }
                 */
                for (unsigned long temp = 0; temp < files_count; temp++)
                    grep_file_process(files[temp], patterns, patterns_count, format_info);
            } else {
                grep_file_process(NULL, patterns, patterns_count, format_info);
            }

            //  Clear patterns:
            if (patterns_count) {
                for (unsigned long temp = 0; temp < patterns_count; temp++)
                    free(patterns[temp]);
                free(patterns);
            }

            //  Clear files:
            if (files_count) {
                for (unsigned long temp = 0; temp < files_count; temp++)
                    free(files[temp]);
                free(files);
            }
        }
    }
    return exit_code;
}

char **read_pattern(char *arg,
                    char **patterns, unsigned long *patterns_count,
                    int *exit_code) {
    unsigned long len = get_word_length(arg);

    if (len) {
        patterns = init_strings(patterns, *patterns_count);
        patterns[*patterns_count] = (char *)malloc((len + 1) * sizeof(char));
        // patterns[*patterns_count] = paste_word(arg, len, patterns[*patterns_count]);
        patterns[*patterns_count] = strcpy(patterns[*patterns_count], arg);
        (*patterns_count)++;
    } else {
        S21_GREP_MESSAGE_ERROR;
        *exit_code = S21_GREP_ERROR_OPTION_ILLEGAL;
    }
    return patterns;
}

char **read_patterns_from_file(char *arg,
                               char **patterns, unsigned long *patterns_count,
                               unsigned short format_info, int *exit_code) {
    unsigned long len = get_word_length(arg);
    if (len) {
        char buffer[4096];
        /*
        for (unsigned short temp = 0; temp < 4096; temp++) {
            buffer[temp] = *arg;
            if (!(*(arg++)))
                break;
        }
        */
        FILE *to_read;
        // if ((to_read = fopen(buffer, "r+"))) {
        if ((to_read = fopen(arg, "r+"))) {
            while (fgets(buffer, 4096, to_read)) {
                patterns = init_strings(patterns, *patterns_count);
                len = strlen(buffer);
                patterns[*patterns_count] = (char *)malloc((len + 1) * sizeof(char));
                // patterns[*patterns_count] = paste_word(buffer, len, patterns[*patterns_count]);
                patterns[*patterns_count] = strcpy(patterns[*patterns_count], buffer);
                (*patterns_count)++;
            }
            fclose(to_read);
        } else {
            process_file_error(buffer, format_info, exit_code);
        }
    } else {
        S21_GREP_MESSAGE_ERROR;
        *exit_code = S21_GREP_ERROR_OPTION_ILLEGAL;
    }
    return patterns;
}

char **init_strings(char **strings, unsigned long strings_count) {
    if (strings_count)
        strings = (char **)realloc(strings, (strings_count + 1) * sizeof(char *));
    else
        strings = (char **)malloc(sizeof(char *));
    return strings;
}

//  Some common function for word processing
/*
char *paste_word(const char *word, unsigned long word_length,
                 char *where) {
    where[word_length--] = '\0';
    for (; word_length; word_length--)
        where[word_length] = word[word_length];
    return where;
}
 */
unsigned long get_word_length(const char *word) {
    unsigned long word_length = 0;
    char *word_iter = (char *)word;
    for (; *word_iter; word_iter++) {
        if (*word_iter == ' ')
            break;
        word_length++;
    }
    return word_length;
}

int grep_file_process(  // FILE *to_check,
                      char *file_name,
                      char **patterns, unsigned long patterns_count,
                      unsigned short format_info) {
    FILE *to_check;
    if (file_name)
        to_check = fopen(file_name, "r+");
    else
        to_check = stdin;
    //  If opened:
    if (to_check) {
        char buffer[4096];
        unsigned long result_count = 0;
        unsigned long current_line = 0;

        regex_t regex;
        int regflag = 0;
        if (format_info & S21_GREP_FORMAT_SET_NOCASE)
            regflag |= REG_ICASE;

        while (fgets(buffer, 4096, to_check)) {
            /*
            char *result = NULL;
            current_line++;
            for (unsigned long temp = 0; temp < patterns_count; temp++) {
                if (format_info & S21_GREP_FORMAT_SET_NOCASE) {
                    //  DO IT
                } else if ((result = strstr(buffer, patterns[temp]))) {
                    break;
                }
            }
            if (result && !(format_info & S21_GREP_FORMAT_SET_INVERT))
                result_count += you_did_it_yaaay(buffer, format_info, file_name, current_line);
            else if (!result && (format_info & S21_GREP_FORMAT_SET_INVERT))
                result_count += you_did_it_yaaay(buffer, format_info, file_name, current_line);
            */
            current_line++;
            for (unsigned long temp = 0; temp < patterns_count; temp++) {
                regcomp(&regex, patterns[temp], regflag);
                int result = regexec(&regex, buffer, 0, NULL, 0);
                //  Print result:
                if ((!result && !(format_info & S21_GREP_FORMAT_SET_INVERT)) ||
                    (result && (format_info & S21_GREP_FORMAT_SET_INVERT))) {
                    //  Print file name:
                    if (!(format_info & S21_GREP_FORMAT_SET_LINES_NONAME)) {
                        // if (!(format_info & S21_GREP_FORMAT_SET_PARTIAL) ||
                        //    (format_info & S21_GREP_FORMAT_SET_INVERT) ||
                        //    !result_count)
                            printf("%s:", file_name);
                    }
                    //  Print result:
                        //  Files only + count
                    if ((format_info & S21_GREP_FORMAT_SET_FILES) &&
                        (format_info & S21_GREP_FORMAT_SET_LINES)) {
                        printf("%d\n%s\n", 1, file_name);
                    } else {
                        if (!(format_info & S21_GREP_FORMAT_SET_LINES)) {
                            if (format_info & S21_GREP_FORMAT_SET_NUMERATE)
                                printf("%lu:", current_line);
                            //  Partial, non-invert, non-count-only
                            if ((format_info & S21_GREP_FORMAT_SET_PARTIAL) &&
                                // !(format_info & S21_GREP_FORMAT_SET_LINES) &&
                                !(format_info & S21_GREP_FORMAT_SET_INVERT)) {
                                //  printf("test\n");
                                regmatch_t regmatch;
                                char *buffer_iter = buffer;
                                while (!regexec(&regex, buffer_iter, 1, &regmatch, 0)) {
                                    result_count++;
                                    buffer_iter += regmatch.rm_so;
                                    for (int temp_iter = 0;
                                             temp_iter < regmatch.rm_eo - regmatch.rm_so;
                                             temp_iter++) {
                                        printf("%c", *buffer_iter);
                                        buffer_iter++;
                                    }
                                    printf("\n");
                                }
                            } else {
                                result_count++;
                                printf("%s", buffer);
                            }
                        } else {
                            result_count++;
                            printf("%lu\n", result_count);
                        }
                    }
                    regfree(&regex);
                    break;
                }
                regfree(&regex);
            }
            // if (format_info & S21_GREP_FORMAT_)
        }
        fclose(to_check);
    // If can't open:
    } else {
        process_file_error(file_name, format_info, NULL);
    }

    // printf("%lu\n", result_count);
    return 0;
}

char **set_files(int argc, char *argv[], int iter,
                 char **files, unsigned long *files_count) {
    while (iter < argc) {
        if (*argv[iter] == S21_GREP_FLAG_CHECK) {
            char *arg_iter = argv[iter] + 1;
            if (*arg_iter == S21_GREP_FORMAT_PATTERN ||
                *arg_iter == S21_GREP_FORMAT_FROMFILE) {
                if (!(*(++arg_iter)))
                    iter++;
            }
        } else {
            // printf("%s\n", argv[iter]);
            files = init_strings(files, *files_count);
            files[*files_count] = (char *)malloc((strlen(argv[iter]) + 1) * sizeof(char));
            // files[*files_count] = paste_word(argv[iter], strlen(argv[iter] + 1), files[*files_count]);
            files[*files_count] = strcpy(files[*files_count], argv[iter]);
            // printf("%s\n", files[*files_count]);
            (*files_count)++;
        }
        iter++;
    }
    return files;
}

void process_file_error(char *file_name,
                        unsigned short format_info, int *exit_code) {
    if (!(format_info & S21_GREP_FORMAT_SET_SUPPRESS)) {
        if (errno == ENOENT) {
            if (exit_code)
                *exit_code = S21_GREP_ERROR_FILE_ABSENT;
            S21_GREP_MESSAGE_FILE_ABSENT(file_name);
        } else {
            if (exit_code)
                *exit_code = S21_GREP_ERROR_FILE_IS_DIR;
            S21_GREP_MESSAGE_FILE_IS_DIR(file_name);
        }
    }
}
/*
unsigned long you_did_it_yaaay(char *output, unsigned short format_info,
                               char *file_name, unsigned long current_line) {
    unsigned long count_the_goods = 0;
    char last_wasnt_name = 0;
    
    // Main check for name input:
    if (!(format_info & S21_GREP_FORMAT_SET_LINES_NONAME)) {
        printf("%s", file_name);
        last_was_name = 1;
    }
    if (format_info & S21_GREP_FORMAT_SET_LINES)
        count
    
    return count_the_goods;
}
*/
