#ifndef QUICK_LOG_H
#define QUICK_LOG_H

#include "quick_log/quick_ansi.h" // IWYU pragma: keep

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

// --- internal fn decl ---

void q_log(int, const char* const, ...);
void q_log_msg(int, const char* const, const char* const, ...);

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

#define qdbg_m(title, fmt, ...) \
    do { q_log_msg(0, (title), (fmt), ##__VA_ARGS__); } while (0)

#define qinfo(fmt, ...) \
    do { q_log(1, (fmt), ##__VA_ARGS__); } while (0)

#define qinfo_m(title, fmt, ...) \
    do { q_log_msg(1, (title), (fmt), ##__VA_ARGS__); } while (0)

#define qwarn(fmt, ...) \
    do { q_log(2, (fmt), ##__VA_ARGS__); } while (0)

#define qwarn_m(title, fmt, ...) \
    do { q_log_msg(2, (title), (fmt), ##__VA_ARGS__); } while (0)

#define qerr(fmt, ...) \
    do { q_log(3, (fmt), ##__VA_ARGS__); } while (0)

#define qerr_m(title, fmt, ...) \
    do { q_log_msg(3, (title), (fmt), ##__VA_ARGS__); } while (0)

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

#define _LOG_FMT(fmt) do { \
    va_list args;          \
    va_start(args, fmt);   \
    vprintf(fmt, args);    \
    va_end(args);          \
} while (0)

void q_log(int lvl, const char* const msg, ...)
{
    static const char* LVL_LUT[] = {
        qansi_fg_cyan   "[DBUG]",
        qansi_fg_green  "[INFO]",
        qansi_fg_yellow "[WARN]",
        qansi_fg_red    "[ERRO]",
        qansi_fg_black  "[UNKN]",
    };

    if (lvl < 0 || lvl > 3) lvl = 4;

    printf("%s%s : ", LVL_LUT[lvl], qansi(0));
    _LOG_FMT(msg);
    printf("\n");
}

void q_log_msg(int lvl, const char* const title, const char* const msg, ...)
{
    static const char* LVL_LUT[] = {
        qansi_fg_cyan   "[>]",
        qansi_fg_green  "[*]",
        qansi_fg_yellow "[?]",
        qansi_fg_red    "[!]",
        qansi_fg_black  "[:]"
    };

    if (lvl < 0 || lvl > 3) lvl = 4;
    printf(qansi_wrap(1, "%s %s :\n    "), LVL_LUT[lvl], title);
    _LOG_FMT(msg);
    printf("\n");
}

void q_log_hr(void) { printf(qansi_wrap(2, "----------\n")); }
void q_log_br(void) { printf(qansi_reset"\n"); }

void q_log_head(const char* const fmt, ...)
{
    q_log_hr();
    printf("%s", qansi(1));
    _LOG_FMT(fmt);
    printf("%s\n", qansi(0));
    q_log_hr();
}

void q_log_sub_head(const char* const fmt, ...)
{
    printf("\n%s", qansi(1));
    _LOG_FMT(fmt);
    printf("%s\n\n", qansi(0));
}

void q_log_ul(const char* const fmt, ...)
{
    printf(qansi_wrap(2, "- "));
    _LOG_FMT(fmt);
    printf("\n");
}

void q_log_ol(size_t* number, const char* const fmt, ...)
{
    printf(qansi_wrap(2, "%zu. "), number ? (*number)++ : 0);
    _LOG_FMT(fmt);
    printf("\n");
}

void q_log_test(bool cnd, const char* const msg, ...)
{
    static const char* TEST_LUT[] = {
        qansi_fg_red   "[FAIL]",
        qansi_fg_green "[PASS]",
    };

    printf(qansi_wrap(34, "[TEST]"));
    printf("%s%s : ", TEST_LUT[cnd ? 1 : 0], qansi(0));
    _LOG_FMT(msg);
    printf("\n");
}

void q_log_assert(bool cnd, const char* file, int line, const char* const msg, ...)
{
    if (cnd) return;

    printf(qansi_wrap(41, "[ASSERT]"));
    printf(qansi_wrap(2, "[%s:%d]")" : ", file, line);
    _LOG_FMT(msg);
    exit(EXIT_FAILURE);
}

#undef _LOG_FMT

#endif // QUICK_LOG_IMPL

#ifdef __cplusplus
}
#endif

#endif // QUICK_LOG_H
