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

| Macro                | Description                    |
| -------------------- | ------------------------------ |
| `qdbg(msg)`          | Debug message                  |
| `qdbg_m(desc, msg)`  | Detailed Debug message         |
| `qinfo(msg)`         | Informational message          |
| `qinfo_m(desc, msg)` | Detailed Informational message |
| `qwarn(msg)`         | Warning message                |
| `qwarn_m(desc, msg)` | Detailed Warning message       |
| `qerr(msg)`          | Error message                  |
| `qerr_m(desc, msg)`  | Detailed Error message         |
| `qerr_ex(msg)`       | Error message & Exit's process |

**Styling**

| Macro                   | Description                   |
| ----------------------- | ----------------------------- |
| `qbold(text)`           | Text with **bold** stlye      |
| `qunderline(text)`      | Text with **underline** stlye |
| `qhighlight(text)`      | Text with **highlight** stlye |
| `qlog_hr()`             | Logs horizontal row           |
| `qlog_br()`             | Create's a new line           |
| `qlog_head(msg)`        | Logs a heading message        |
| `qlog_subhead(msg)`     | Logs a sub heading            |
| `qlog_ul(msg)`          | Logs a un-ordered list item   |
| `qlog_ol(num_ptr, msg)` | Logs a ordered list item      |

**ANSI Colors**

| Macro                    | Description                               |
| ------------------------ | ----------------------------------------- |
| `qansi(code)`            | Create's ansi escape code                 |
| `qansi_wrap(code, text)` | Wrap's text between ansi code and reset's |

1. _ANSI Styles_

| Macro             | ANSI code |
| ----------------- | --------- |
| `qansi_reset`     | **0**     |
| `qansi_bold`      | **1**     |
| `qansi_dim`       | **2**     |
| `qansi_italic`    | **3**     |
| `qansi_underline` | **4**     |
| `qansi_blink`     | **5**     |
| `qansi_reverse`   | **7**     |
| `qansi_hidden`    | **8**     |
| `qansi_strike`    | **9**     |

2. _ANSI Foreground_

| Macro              | ANSI code |
| ------------------ | --------- |
| `qansi_fg_black`   | **30**    |
| `qansi_fg_red`     | **31**    |
| `qansi_fg_green`   | **32**    |
| `qansi_fg_yellow`  | **33**    |
| `qansi_fg_blue`    | **34**    |
| `qansi_fg_magenta` | **35**    |
| `qansi_fg_cyan`    | **36**    |
| `qansi_fg_white`   | **37**    |

3. _ANSI Foreground (Bright)_

| Macro                 | ANSI code |
| --------------------- | --------- |
| `qansi_fg_ex_black`   | **90**    |
| `qansi_fg_ex_red`     | **91**    |
| `qansi_fg_ex_green`   | **92**    |
| `qansi_fg_ex_yellow`  | **93**    |
| `qansi_fg_ex_blue`    | **94**    |
| `qansi_fg_ex_magenta` | **95**    |
| `qansi_fg_ex_cyan`    | **96**    |
| `qansi_fg_ex_white`   | **97**    |

4. _ANSI Background_

| Macro              | ANSI code |
| ------------------ | --------- |
| `qansi_bg_black`   | **40**    |
| `qansi_bg_red`     | **41**    |
| `qansi_bg_green`   | **42**    |
| `qansi_bg_yellow`  | **43**    |
| `qansi_bg_blue`    | **44**    |
| `qansi_bg_magenta` | **45**    |
| `qansi_bg_cyan`    | **46**    |
| `qansi_bg_white`   | **47**    |

5. _ANSI Background (Bright)_

| Macro                 | ANSI code |
| --------------------- | --------- |
| `qansi_bg_ex_black`   | **100**   |
| `qansi_bg_ex_red`     | **101**   |
| `qansi_bg_ex_green`   | **102**   |
| `qansi_bg_ex_yellow`  | **103**   |
| `qansi_bg_ex_blue`    | **104**   |
| `qansi_bg_ex_magenta` | **105**   |
| `qansi_bg_ex_cyan`    | **106**   |
| `qansi_bg_ex_white`   | **107**   |

**Testing / Assertions**

| Macro                   | Description             |
| ----------------------- | ----------------------- |
| `qtest(cond)`           | Test condition          |
| `qtest_s(cond, desc)`   | Test with description   |
| `qassert(cond)`         | Assert condtion         |
| `qassert_s(cond, desc)` | Assert with description |

## Note

- The `QUICK_LOG_IMPL` macro should be defined in **exactly one** source file.
- Works in both **C** and **C++**.
- No dynamic allocation.
- Intended for **debugging**, **logging**, and **lightweight testing**.
- The **ANSI Foreground (Bright)** & **ANSI Background (Bright)** may not be supported in some platforms.
