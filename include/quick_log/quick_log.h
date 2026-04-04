#ifndef _QUICK_LOG_H
#define _QUICK_LOG_H

typedef enum {
    ANSI_RESET          = 0,
    ANSI_BOLD           = 1,
    ANSI_DIM            = 2,
    ANSI_ITALIC         = 3,
    ANSI_UNDERLINE      = 4,
    ANSI_BLINK          = 5,
    ANSI_INVERSE        = 7,
    ANSI_HIDDEN         = 8,
    ANSI_STRIKETHROUGH  = 9,
} ansi_style;

typedef enum {
    ANSI_BLACK          = 30,
    ANSI_RED            = 31,
    ANSI_GREEN          = 32,
    ANSI_YELLOW         = 33,
    ANSI_BLUE           = 34,
    ANSI_MAGENTA        = 35,
    ANSI_CYAN           = 36,
    ANSI_WHITE          = 37,

    ANSI_BG_BLACK       = 40,
    ANSI_BG_RED         = 41,
    ANSI_BG_GREEN       = 42,
    ANSI_BG_YELLOW      = 43,
    ANSI_BG_BLUE        = 44,
    ANSI_BG_MAGENTA     = 45,
    ANSI_BG_CYAN        = 46,
    ANSI_BG_WHITE       = 47,

    ANSI_EX_BLACK       = 90,
    ANSI_EX_RED         = 91,
    ANSI_EX_GREEN       = 92,
    ANSI_EX_YELLOW      = 93,
    ANSI_EX_BLUE        = 94,
    ANSI_EX_MAGENTA     = 95,
    ANSI_EX_CYAN        = 96,
    ANSI_EX_WHITE       = 97,

    ANSI_BG_EX_BLACK    = 100,
    ANSI_BG_EX_RED      = 101,
    ANSI_BG_EX_GREEN    = 102,
    ANSI_BG_EX_YELLOW   = 103,
    ANSI_BG_EX_BLUE     = 104,
    ANSI_BG_EX_MAGENTA  = 105,
    ANSI_BG_EX_CYAN     = 106,
    ANSI_BG_EX_WHITE    = 107,
} ansi_color;

#endif // _QUICK_LOG_H
