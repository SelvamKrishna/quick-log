#ifndef QUICK_LOG_H
#define QUICK_LOG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

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

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
} log_level;

const char* ansi_style_str(ansi_style);
const char* ansi_color_str(ansi_color);
const char* ansi_reset(void);

const char* log_level_str(log_level);
void q_log(log_level, const char* const, ...);

#define QDBG(msg, ...)  do { q_log(LOG_LEVEL_DEBUG, msg, ...); } while (0)
#define QINFO(msg, ...) do { q_log(LOG_LEVEL_INFO , msg, ...); } while (0)
#define QWARN(msg, ...) do { q_log(LOG_LEVEL_WARN , msg, ...); } while (0)
#define QERR(msg, ...)  do { q_log(LOG_LEVEL_ERROR, msg, ...); } while (0)

#define QVAR(var) Q_DBG(#var, (var))

#ifdef QUICK_LOG_IMPL

#include <stdio.h>
#include <stdarg.h>

static const char* TAGS[] = { "DBUG", "INFO", "WARN", "ERRO" };
static const ansi_color COLOR[] = { ANSI_BLUE, ANSI_GREEN, ANSI_YELLOW, ANSI_RED };

const char* ansi_style_str(ansi_style code)
{
    static char buf[16];
    snprintf(buf, sizeof(buf), "\033[%dm", code);
    return buf;
}

const char* ansi_color_str(ansi_color code)
{
    static char buf[16];
    snprintf(buf, sizeof(buf), "\033[%dm", code);
    return buf;
}

const char* ansi_reset(void) { return "\033[0m"; }

const char* log_level_str(log_level lvl)
{
    static char buf[32];
    snprintf(buf, sizeof(buf), "\033[1;%dm[%s]\033[0m", COLOR[lvl], TAGS[lvl]);
    return buf;
}

void q_log(log_level lvl, const char* const msg, ...)
{
    printf("%s : ", log_level_str(lvl));

    va_list args;
    va_start(args, msg);
    vprintf(msg, args);
    va_end(args);

    printf("\n");
}

#endif // QUICK_LOG_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_LOG_H
