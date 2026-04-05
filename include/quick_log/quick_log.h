#ifndef QUICK_LOG_H
#define QUICK_LOG_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// --- internal fn decl ---

void q_log(int, const char* const, ...);
void q_log_hr(void);
void q_log_head(const char* const, ...);
void q_log_test(bool, const char* const, ...);
void q_log_assert(bool, const char*, int, const char* const, ...);

// --- public API ---

#define qdbg(fmt, ...) \
    do { q_log(0, (fmt), ##__VA_ARGS__); } while (0)

#define qinfo(fmt, ...) \
    do { q_log(1, (fmt), ##__VA_ARGS__); } while (0)

#define qwarn(fmt, ...) \
    do { q_log(2, (fmt), ##__VA_ARGS__); } while (0)

#define qerr(fmt, ...) \
    do { q_log(3, (fmt), ##__VA_ARGS__); } while (0)

#define qhr() \
    do { q_log_hr(); } while (0)

#define qhead(text, ...) \
    do { q_log_head((text), ##__VA_ARGS__); } while (0)

#define qtest(cnd) \
    do { q_log_test((cnd), #cnd); } while (0)

#define qtest_s(cnd, fmt, ...) \
    do { q_log_test((cnd), fmt, ##__VA_ARGS__); } while (0)

#define qassert(cnd) \
    do { q_log_assert((cnd), __FILE__, __LINE__, #cnd); } while (0)

#define qassert_s(cnd, fmt, ...) \
    do { q_log_assert((cnd), __FILE__, __LINE__, fmt, ##__VA_ARGS__); } while (0)

// --- logic impl ---

#ifdef QUICK_LOG_IMPL

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define _LOG_FMT_ARGS(fmt) \
    do {                     \
        va_list args;        \
        va_start(args, fmt); \
        vprintf(fmt, args);  \
        va_end(args);        \
    } while (0)

#define _ANSI_CODE(code) \
    "\033[" #code "m"

void q_log(int lvl, const char* const msg, ...)
{
    static const char* LVL_LUT[] = {
        _ANSI_CODE(36) "[DBUG]",
        _ANSI_CODE(32) "[INFO]",
        _ANSI_CODE(33) "[WARN]",
        _ANSI_CODE(31) "[ERRO]"
    };

    if (lvl < 0 || lvl > 3) return;

    printf("%s%s : ", LVL_LUT[lvl], _ANSI_CODE(0));
    _LOG_FMT_ARGS(msg);
    printf("\n");
}

void q_log_hr(void) { printf("---\n"); }

void q_log_head(const char* const heading, ...)
{
    q_log_hr();
    printf("%s", _ANSI_CODE(1));
    _LOG_FMT_ARGS(heading);
    printf("%s\n", _ANSI_CODE(0));
    q_log_hr();
}

void q_log_test(bool cnd, const char* const msg, ...)
{
    static const char* TEST_LUT[] = {
        _ANSI_CODE(31) "[FAIL]",
        _ANSI_CODE(32) "[PASS]",
    };

    printf("%s[TEST]%s", _ANSI_CODE(34), _ANSI_CODE(0));
    printf("%s%s : ", TEST_LUT[cnd ? 1 : 0], _ANSI_CODE(0));
    _LOG_FMT_ARGS(msg);
    printf("\n");
}

void q_log_assert(bool cnd, const char* file, int line, const char* const msg, ...)
{
    if (cnd) return;

    printf("%s[ASSERT]%s", _ANSI_CODE(41), _ANSI_CODE(0));
    printf("%s[%s:%d]%s : ", _ANSI_CODE(1), file, line, _ANSI_CODE(0));
    _LOG_FMT_ARGS(msg);
    exit(EXIT_FAILURE);
}

#undef _LOG_FMT_ARGS
#undef _ANSI_CODE

#endif // QUICK_LOG_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_LOG_H
