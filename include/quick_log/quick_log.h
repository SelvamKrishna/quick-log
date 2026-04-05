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

const char* ansi_style_str(ansi_style);
const char* ansi_color_str(ansi_color);
const char* ansi_reset(void);

typedef enum {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
} log_level;

const char* log_level_str(log_level);

void q_log(log_level, const char* const, ...);

#define qdbg(msg, ...)  do { q_log(LOG_LEVEL_DEBUG, (msg), ##__VA_ARGS__); } while (0)
#define qinfo(msg, ...) do { q_log(LOG_LEVEL_INFO , (msg), ##__VA_ARGS__); } while (0)
#define qwarn(msg, ...) do { q_log(LOG_LEVEL_WARN , (msg), ##__VA_ARGS__); } while (0)
#define qerr(msg, ...)  do { q_log(LOG_LEVEL_ERROR, (msg), ##__VA_ARGS__); } while (0)

void q_log_hr(void);
void q_log_head(const char* const, ...);

#define qhead(heading, ...) do { q_log_head((heading), ##__VA_ARGS__); } while (0)
#define qhr() do { q_log_hr(); } while (0)

void q_log_test(bool, const char* const, ...);

#define qtest(cnd) do { q_log_test((cnd), #cnd); } while (0)
#define qtest_s(cnd, msg, ...) do { q_log_test((cnd), msg, ##__VA_ARGS__); } while (0)

void q_log_assert_ext(bool, const char*, int, const char* const, ...);

#define qassert(cnd) do { q_log_assert_ext((cnd), __FILE__, __LINE__, #cnd); } while (0)

#define qassert_s(cnd, msg, ...) do { \
    q_log_assert_ext((cnd), __FILE__, __LINE__, msg, ##__VA_ARGS__); \
} while (0)

#ifdef QUICK_LOG_IMPL

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static const char* TAGS[] = { "DBUG", "INFO", "WARN", "ERRO" };
static const ansi_color COLOR[] = { ANSI_CYAN, ANSI_GREEN, ANSI_YELLOW, ANSI_RED };

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
    snprintf(buf, sizeof(buf), "\033[%dm[%s]\033[0m", COLOR[lvl], TAGS[lvl]);
    return buf;
}

#define _LOG_FMT_ARGS(f_str) do { \
    va_list args;                 \
    va_start(args, f_str);        \
    vprintf(f_str, args);         \
    va_end(args);                 \
} while (0)

void q_log(log_level lvl, const char* const msg, ...)
{
    printf("%s : ", log_level_str(lvl));
    _LOG_FMT_ARGS(msg);
    printf("\n");
}

void q_log_hr(void) { printf("---\n"); }

void q_log_head(const char* const heading, ...)
{
    q_log_hr();
    printf("%s", ansi_style_str(ANSI_BOLD));
    _LOG_FMT_ARGS(heading);
    printf("%s\n", ansi_reset());
    q_log_hr();
}

void q_log_test(bool cnd, const char* const msg, ...)
{
    char* cnd_res   = (cnd) ? "[PASS]" : "[FAIL]";
    ansi_color code = (cnd) ? ANSI_GREEN : ANSI_RED;

    printf("%s[TEST]%s", ansi_color_str(ANSI_BLUE), ansi_reset());
    printf("%s%s%s : ", ansi_color_str(code), cnd_res, ansi_reset());
    _LOG_FMT_ARGS(msg);
    printf("\n");
}

void q_log_assert_ext(bool cnd, const char* file, int line, const char* const msg, ...)
{
    if (cnd) return;

    printf("%s[ASSERT]%s", ansi_color_str(ANSI_BG_RED), ansi_reset());
    printf(
        "%s[%s:%d]%s : ",
        ansi_style_str(ANSI_BOLD), file, line, ansi_reset()
    );
    _LOG_FMT_ARGS(msg);
    exit(EXIT_FAILURE);
}

#undef _LOG_FMT_ARGS

#endif // QUICK_LOG_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_LOG_H
