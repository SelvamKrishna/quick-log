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
void q_log_br(void);
void q_log_head(const char* const, ...);
void q_log_sub_head(const char* const, ...);
void q_log_ul(const char* const, ...);
void q_log_ol(size_t*, const char* const, ...);

void q_log_test(bool, const char* const, ...);
void q_log_assert(bool, const char*, int, const char* const, ...);

// --- public API ---

// leveled logging:

#define qdbg(fmt, ...) \
    do { q_log(0, (fmt), ##__VA_ARGS__); } while (0)

#define qinfo(fmt, ...) \
    do { q_log(1, (fmt), ##__VA_ARGS__); } while (0)

#define qwarn(fmt, ...) \
    do { q_log(2, (fmt), ##__VA_ARGS__); } while (0)

#define qerr(fmt, ...) \
    do { q_log(3, (fmt), ##__VA_ARGS__); } while (0)

#define qerr_ex(fmt, ...) \
    do { q_log(3, (fmt), ##__VA_ARGS__); exit(EXIT_FAILURE); } while (0)

// styled logging:

#define qbold(text)      "\033[1m"  text "\033[0m"
#define qunderline(text) "\033[4m"  text "\033[0m"
#define qhighlight(text) "\033[47m" text "\033[0m"

#define qlog_hr() \
    do { q_log_hr(); } while (0)

#define qlog_br() \
    do { q_log_br(); } while (0)

#define qlog_head(fmt, ...) \
    do { q_log_head((fmt), ##__VA_ARGS__); } while (0)

#define qlog_subhead(fmt, ...) \
    do { q_log_sub_head(fmt, ##__VA_ARGS__); } while (0)

#define qlog_ul(fmt, ...) \
    do { q_log_ul(fmt, ##__VA_ARGS__); } while (0)

#define qlog_ol(num_ptr, fmt, ...) \
    do { q_log_ol(num_ptr, fmt, ##__VA_ARGS__); } while (0)

// testing and assertion:

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

#define _LOG_FMT(fmt) \
    do {                     \
        va_list args;        \
        va_start(args, fmt); \
        vprintf(fmt, args);  \
        va_end(args);        \
    } while (0)

#define _ANSI(code) "\033[" #code "m"
#define _ANSI_WRAP(code, text) _ANSI(code) text _ANSI(0)

void q_log(int lvl, const char* const msg, ...)
{
    static const char* LVL_LUT[] = {
        _ANSI(36) "[DBUG]",
        _ANSI(32) "[INFO]",
        _ANSI(33) "[WARN]",
        _ANSI(31) "[ERRO]"
    };

    if (lvl < 0 || lvl > 3) return;

    printf("%s%s : ", LVL_LUT[lvl], _ANSI(0));
    _LOG_FMT(msg);
    printf("\n");
}

void q_log_hr(void) { printf(_ANSI_WRAP(2, "----------\n")); }
void q_log_br(void) { printf(_ANSI(0)"\n"); }

void q_log_head(const char* const fmt, ...)
{
    q_log_hr();
    printf("%s", _ANSI(1));
    _LOG_FMT(fmt);
    printf("%s\n", _ANSI(0));
    q_log_hr();
}

void q_log_sub_head(const char* const fmt, ...)
{
    printf("\n%s", _ANSI(1));
    _LOG_FMT(fmt);
    printf("%s\n\n", _ANSI(0));
}

void q_log_ul(const char* const fmt, ...)
{
    printf(_ANSI_WRAP(2, "- "));
    _LOG_FMT(fmt);
    printf("\n");
}

void q_log_ol(size_t* number, const char* const fmt, ...)
{
    printf(_ANSI_WRAP(2, "%zu. "), number ? (*number)++ : 0);
    _LOG_FMT(fmt);
    printf("\n");
}

void q_log_test(bool cnd, const char* const msg, ...)
{
    static const char* TEST_LUT[] = {
        _ANSI(31) "[FAIL]",
        _ANSI(32) "[PASS]",
    };

    printf(_ANSI_WRAP(34, "[TEST]"));
    printf("%s%s : ", TEST_LUT[cnd ? 1 : 0], _ANSI(0));
    _LOG_FMT(msg);
    printf("\n");
}

void q_log_assert(bool cnd, const char* file, int line, const char* const msg, ...)
{
    if (cnd) return;

    printf("%s[ASSERT]%s", _ANSI(41), _ANSI(0));
    printf("%s[%s:%d]%s : ", _ANSI(2), file, line, _ANSI(0));
    _LOG_FMT(msg);
    exit(EXIT_FAILURE);
}

#undef _LOG_FMT
#undef _ANSI
#undef _ANSI_WRAP

#endif // QUICK_LOG_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_LOG_H
