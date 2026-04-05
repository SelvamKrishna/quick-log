// #define QUICK_LOG_IMPL // flags the implementation of the library
#include <quick_log/quick_log.h>

int main(void)
{
    int a = 14;

    qhead("Log Levels Showcase");
    qdbg("Allocated (%zu) bytes at (%p)", sizeof(int), &a);
    qinfo("Initialized renderer");
    qwarn("Engine can be initialized only one");
    qerr("Process failed with code = %d", 404);

    qhead("Testing Showcase");
    qtest(a == 14);
    qtest(a != 14);
    qtest_s(false, "Failing test");
    qtest_s(true , "Passing test");

    qhead("Assertion Showcase");
    qassert(a == 14);
    qassert_s(a != 14, "a should not be equal to 14");

    return 0;
}
