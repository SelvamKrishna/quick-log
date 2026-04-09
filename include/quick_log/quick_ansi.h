#ifndef QUICK_ANSI_H
#define QUICK_ANSI_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// --- public API ---

#define qansi(code) "\033[" #code "m"
#define qansi_wrap(code, text) "\033[" #code "m" text "\033[0m"

#define qansi_reset         "\033[0m"
#define qansi_bold          "\033[1m"
#define qansi_dim           "\033[2m"
#define qansi_italic        "\033[3m"
#define qansi_underline     "\033[4m"
#define qansi_blink         "\033[5m"
#define qansi_reverse       "\033[7m"
#define qansi_hidden        "\033[8m"
#define qansi_strike        "\033[9m"

#define qansi_fg_black      "\033[30m"
#define qansi_fg_red        "\033[31m"
#define qansi_fg_green      "\033[32m"
#define qansi_fg_yellow     "\033[33m"
#define qansi_fg_blue       "\033[34m"
#define qansi_fg_magenta    "\033[35m"
#define qansi_fg_cyan       "\033[36m"
#define qansi_fg_white      "\033[37m"
#define qansi_fg_ex_black   "\033[90m"
#define qansi_fg_ex_red     "\033[91m"
#define qansi_fg_ex_green   "\033[92m"
#define qansi_fg_ex_yellow  "\033[93m"
#define qansi_fg_ex_blue    "\033[94m"
#define qansi_fg_ex_magenta "\033[95m"
#define qansi_fg_ex_cyan    "\033[96m"
#define qansi_fg_ex_white   "\033[97m"

#define qansi_bg_black      "\033[40m"
#define qansi_bg_red        "\033[41m"
#define qansi_bg_green      "\033[42m"
#define qansi_bg_yellow     "\033[43m"
#define qansi_bg_blue       "\033[44m"
#define qansi_bg_magenta    "\033[45m"
#define qansi_bg_cyan       "\033[46m"
#define qansi_bg_white      "\033[47m"
#define qansi_bg_ex_black   "\033[100m"
#define qansi_bg_ex_red     "\033[101m"
#define qansi_bg_ex_green   "\033[102m"
#define qansi_bg_ex_yellow  "\033[103m"
#define qansi_bg_ex_blue    "\033[104m"
#define qansi_bg_ex_magenta "\033[105m"
#define qansi_bg_ex_cyan    "\033[106m"
#define qansi_bg_ex_white   "\033[107m"

#ifdef __cplusplus
}
#endif

#endif // QUICK_ANSI_H
