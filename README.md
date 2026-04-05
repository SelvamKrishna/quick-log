# Quick Log

A _minimal_, _header-only_ logging library for **C** & **C++**.

## Usage

**Clone**

```shell
git clone https://github.com/SelvamKrishna/quick-log.git
```

_or just copy the `include/quick_log` directory into your project._

**Include**

```c
#define QUICK_LOG_IMPL // ONLY DEFINE IN ONE SOURCE FILE
#include <quick_log/quick_log.h>
```

**CMake (optional)**

```cmake
add_subdirectory(quick-log)
target_link_libraries(your_target PRIVATE quick-log)
```

_or header-only-usage:_

```cmake
target_include_directories(your_target PRIVATE path/to/quick-log/include)
```

## API

**Logging**

| Macro        | Description           |
| ------------ | --------------------- |
| `qdbg(msg)`  | Debug Message         |
| `qinfo(msg)` | Informational Message |
| `qwarn(msg)` | Warning Message       |
| `qerr(msg)`  | Error Message         |

**Structure**

| Macro         | Description           |
| ------------- | --------------------- |
| `qhead(text)` | Section/header output |
| `qhr()`       | Horizontal line break |

**Testing / Assertions**

| Macro                   | Description             |
| ----------------------- | ----------------------- |
| `qtest(cond)`           | Test condition          |
| `qtest_s(cond, desc)`   | Test with description   |
| `qassert(cond)`         | Assert condtion         |
| `qassert_s(cond, desc)` | Assert with description |

## Note

- the `QUICK_LOG_IMPL` macro should be defined in **exactly one** source file.
- Works in both **C and C++**.
- No dynamic allocation.
- Intended for **debugging**, **diagnostics**, and **lightweight testing**.
