#define QUICK_LOG_IMPL // flags the implementation of the library
#include <quick_log/quick_log.h>

int main(void)
{
    int a = 14;

    qlog_head("Log Levels Showcase");
    qdbg("Allocated (%zu) bytes at (%p)", sizeof(int), &a);
    qinfo("Initialized renderer");
    qwarn("Engine can be initialized only one");
    qerr("Process failed with code = %d", 404);
    // qerr_ex("Will kill the program"); // Uncomment to test

    size_t line_n = 0;
    qlog_head("Styles Showcase");
    qlog_subhead("Sub Head 1");
    qlog_ul("Point A");
    qlog_ul("Point B");
    qlog_ul("Point C");
    qlog_subhead("Sub Head 2");
    qlog_ol(&line_n, "Point A");
    qlog_ol(&line_n, "Point B");
    qlog_ol(&line_n, "Point C");
    qlog_subhead("Sub Head 3");
    printf("This is a "qbold("bold")" message.\n");
    printf("This is a "qunderline("underlined")" message.\n");
    printf("This is a "qhighlight("highlight")" message.\n");
    qlog_br();

    qlog_head("Testing / Assertion Showcase");
    qtest(a == 14);
    qtest(a != 14);
    qtest_s(false, "Failing test");
    qtest_s(true , "Passing test");
    qassert(a == 14);
    qassert_s(a != 14, "a should not be equal to 14");

    return 0;
}
