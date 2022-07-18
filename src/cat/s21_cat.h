#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

//  ----------------------------------------------------------------------------------------
//                                          FLAGS
//  ----------------------------------------------------------------------------------------
#ifndef _S21_CAT_FLAGS
#define _S21_CAT_FLAGS
//  1)  Flag symbol:
#define S21_CAT_FLAG_CHECK              '-'     //  Flag look-for symbol
#define S21_CAT_FLAG_NUMERATE           'b'     //  Number the non-blank output lines, starting at 1.
#define S21_CAT_FLAG_NUMERATE_BLANK     'n'     //  Number the output lines, starting at 1.
#define S21_CAT_FLAG_SQUEEZE            's'     //  Squeeze multiple adjacent empty lines, causing the
                                                //  output to be single spaced.
#define S21_CAT_FLAG_NONPRINTING        'v'     //  Display non-printing characters so they are visible.
                                                //  Control characters print as `^X' for control-X; the
                                                //  delete character (octal 0177) prints as `^?'.
                                                //  Non-ASCII characters (with the high bit set) are printed
                                                //  as `M-' (for meta) followed by the character for the low
                                                //  7 bits.
#define S21_CAT_FLAG_NONPRINTING_END    'e'     //  Display non-printing characters (see the -v option), and
                                                //  display a dollar sign (`$') at the end of each line.
#define S21_CAT_FLAG_NONPRINTING_TAB    't'     //  Display non-printing characters (see the -v option), and
                                                //  display tab characters as `^I'.
#define S21_CAT_FLAG_BUFFERING_DISABLE  'u'     //  Disable output buffering.
//  Linux special:
#define S21_CAT_FLAG_END                'E'     //  $
#define S21_CAT_FLAG_TAB                'T'     //  tabs
#define S21_CAT_FLAG_ALL                'A'     //  vET

//  2)  Flag bit:
#define S21_CAT_FORMAT_SET_NUMERATE_BLANK       1       //  Numerate blank lines        (n)
#define S21_CAT_FORMAT_SET_NUMERATE_NONBLANK    2       //  Numerate non-blank lines    (b, n)
#define S21_CAT_FORMAT_SET_SQUEEZE              4       //  Leave only one empty line   (s)
#define S21_CAT_FORMAT_SET_NONPRINTING          8       //  Print non-printing          (v, e, t)
#define S21_CAT_FORMAT_SET_END                  16      //  Print end-symbol            (e)
#define S21_CAT_FORMAT_SET_TAB                  32      //  Print tab as command        (t)
#define S21_CAT_FORMAT_BUFFERING_DISABLE        64      //  Disable buffering (ignored) (u)


//  ----------------------------------------------------------------------------------------
//                               SPECIAL CHARACTERS AS STRINGS
//  ----------------------------------------------------------------------------------------
#endif  // _S21_CAT_FLAGS

#ifndef _S21_CAT_SPECIAL_CHARS
#define _S21_CAT_SPECIAL_CHARS

#define S21_CAT_SPECIAL_LIST                                                    \
                                     {'@', 'A', 'B',  'C', 'D',  'E', 'F', 'G', \
                                      'H', 'I', 'J',  'K', 'L',  'M', 'N', 'O', \
                                      'P', 'Q', 'R',  'S', 'T',  'U', 'V', 'W', \
                                      'X', 'Y', 'Z',  '[', '\\', ']', '^', '_'  \
                                      }
#define S21_CAT_SPECIAL_DEL           '?'

#endif  // _S21_CAT_SPECIAL_CHARS


//  ----------------------------------------------------------------------------------------
//                                         MACRO
//  ----------------------------------------------------------------------------------------
#ifndef _S21_CAT_MESSAGES
#define _S21_CAT_MESSAGES

#define S21_CAT_MESSAGE_OPTION_ILLEGAL(FLAG)               {\
        printf("cat: illegal option -- %c\n", FLAG);        \
        printf("usage: cat [-benstuv] [file ...]\n");       \
}
#define S21_CAT_MESSAGE_FILE_ABSENT(PATH)                   \
        printf("cat: %s: No such file or directory\n", PATH)

#define S21_CAT_MESSAGE_FILE_IS_DIR(PATH)                   \
        printf("cat: %s: Is a directory\n", PATH)

#endif  // _S21_CAT_MESSAGES

//   --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --  --

#define S21_CAT_NUMERATE_LINE(CURRENT_LINE)                    {\
    unsigned char length = 0;                                   \
    for (unsigned long temp = CURRENT_LINE; temp; temp /= 10)   \
        length++;                                               \
    for (length = 6 - length; length; length--)                 \
        printf(" ");                                            \
    printf("%lu\t", CURRENT_LINE);                              \
}
//  ----------------------------------------------------------------------------------------
//                                         ERRORS
//  ----------------------------------------------------------------------------------------
#ifndef _S21_CAT_ERRORS
#define _S21_CAT_ERRORS

#define S21_CAT_ERROR_OPTION_ILLEGAL    1
#define S21_CAT_ERROR_FILE_ABSENT       1
#define S21_CAT_ERROR_FILE_IS_DIR       1

#endif  // _S21_CAT_ERRORS

#endif  // SRC_CAT_S21_CAT_H_
