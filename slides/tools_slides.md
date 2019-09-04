% Tools
% Alex Hirsch

# Text editor / IDE

## Lots of Options

- Nano
- Vim / Emacs
- VSCode / Atom
- CLion / Eclipse / Qt Creator / …
- Visual Studio

## What's Important

- Being productive
  - Autocompletion
  - Go to definition
  - Debugger integration
- Ergonomics
  - Multi-cursor
  - Forward / backward like in your browser
  - Quickly switch between header / source file

---

![Hover Info](images/hover_info.png)

---

![Argument Info](images/argument_info.png)

---

![Continuous Checking](images/continuous_checking.png)

## 80% / 19% / 1%

- 80% (Visual Studio)
  - Prefer ergonomics
  - Optimise your workflow
- 19% (VSCode)
  - Cover multiple languages
  - Good out-of-the-box experience
  - Use something that's mainstream
- 1% (Vim)
  - Feature rich
  - Macro support
  - Can be scripted
  - Can be used inside a terminal (over SSH)

## Code Navigation

- Use your IDE
- `grep` / Silver Searcher / ripgrep
- Ctags / GNU Global
- Language servers (cquery)

---

![Code Outline](images/va_outline.png)

# Compiler

## Configurations

- Always enable warnings (`-Wall -Wextra -pedantic`)
  - There are even more!
  - Try to have as few warnings as possible
  - Suppress them in special cases
- Debug vs. release build:
  - Optimisations disabled / enabled
  - Assertions enabled / disable
  - Debug symbols enabled / disabled

## Phases

![Compilation Process](images/compilation_process.png)

# Build System

## Advanced (Build System Generators)

- CMake (covered later)
- Autotools
- SCons
- Meson
- MSBuild

## Make

- Often used as back-end by build systems generators
- Can be used for various different tasks / languages
- Suitable for small projects consisting of a few source files
- Checks timestamps for outdated targets
- Tab required for indentation
- First target is built by default (typically called `all`)

---

```make
example: example.c other.c
    gcc -Wall -Wextra -o example example.c other.c
```

---

```make
example: example.c other.c
    gcc -Wall -Wextra -o $@ $^
```

---

```make
CFLAGS = -Wall -Wextra

example: example.c other.c
    $(CC) $(CFLAGS) -o $@ $^
```

---

```make
CFLAGS = -Wall -Wextra

all: example

clean:
    $(RM) example

example: example.c other.c
```

```
$ make
cc -Wall -Wextra    example.c other.c   -o example

$ make clean
rm -f example
```

---

```make
CFLAGS = -Wall -Wextra

all: example

clean:
    $(RM) example example.o example.o

example: example.o other.o
```

```
$ make
cc -Wall -Wextra   -c -o example.o example.c
cc -Wall -Wextra   -c -o other.o other.c
cc   example.o other.o   -o example

$ make clean
rm -f example example.o other.o
```

---

```
%.html: %.md
    $(PAN) $(PANFLAGS) $(PANFLAGS_DOC) -o $@ $^

%.pdf: %.html
    $(HTMLTOPDF) $(HTMLTOPDFFLAGS) --print-to-pdf=$@ "file://$(WD)/$<?print-pdf"

%_slides.html: %_slides.md
    $(PAN) $(PANFLAGS) $(PANFLAGS_SLIDES) -o $@ $^
```

---

- Utilise implicit rules and patterns
- Note `LDFLAGS` and `LDLIBS`
- Mark non-file rules with `.PHONY`

```make
SRC  = $(wildcard *.md)
HTML = $(SRC:.md=.html)
```

# Checking

## Static Analysers

- Cppcheck
- Clang-Tidy
- Visual Studio's `/analyze`

## Runtime Analyser

- Valgrind
- Dr. Memory
- strace / ltrace

---

```c
int uninitialized;
if (uninitialized)
```

```
==12665== Conditional jump or move depends on uninitialised value(s)
==12665==    at 0x108602: main (uninitialized.c:4)
```

---

```c
char *buf = malloc(256);
buf[256] = 42;
```

```
==12784== Invalid write of size 1
==12784==    at 0x10866A: main (invalid_write.c:4)
==12784==  Address 0x522d140 is 0 bytes after a block of size 256 alloc'd
==12784==    at 0x4C2FB0F: malloc (in /usr/lib/valgrind/vgpreload_memcheck-amd64-linux.so)
==12784==    by 0x10865B: main (invalid_write.c:3)
```

## Profiling

- gprof
- Google Performance Tools (gperftools)

---

![Profiler](images/profiler.png)

---

![Callgrind](images/callgrind.png)

# Debugging

## Meet GDB

- Often used as backend for IDE debugger integration
- Can be used from the command-line
- Feature rich
- Scriptable (Python API)
- Go to tool for reverse engineering and binary exploitation

## Basic Commands

- `run` / `start`
- `breakpoint` / `info breakpoints` / `delete`
- `continue`
- `step` / `next` / `finish`
- `print` / `x`
- `list` / `where`
- `info locals` / `info args`
- `help` / `quit`

## Navigating the Stack

- `backtrace`
- `up` / `down`

---

![Stack](images/stack_frames.png)

## Custom Config

- Gdbinit
- GDB dashboard
- pwndbg

---

![GDB Dashboard](images/gdb_dashboard.png)

---

![Debug Hover Info](images/hover_info_dbg.png)

# Formatting

## Clang-Format

- Use Clang-Format for C/C++ code
- Highly customisable
- Very capable
- Text editor / IDE integration (format on save)

---

```clang-format
---
BasedOnStyle: LLVM
ColumnLimit: 120
IndentWidth: 8
TabWidth: 8
UseTab: ForIndentation
BreakBeforeBraces: Linux
AlignEscapedNewlines: DontAlign
AllowShortFunctionsOnASingleLine: Empty
AllowShortIfStatementsOnASingleLine: false
IndentCaseLabels: false
BinPackParameters: false
...
```

## Editorconfig

- Sets basic editor settings (e.g. indentation) depending on the file extension
- Simple configuration file
- All modern editors support it (via plugins)

---

```editorconfig
root = true

[*]
charset = utf-8
end_of_line = lf
insert_final_newline = true
trim_trailing_whitespace = true
indent_style = tab
indent_size = 8

[*.json]
indent_style = space
indent_size = 2
```

# Exercises

## Setting up your IDE

- Setup your favourite text editor / IDE
- Play around with features like debugger integration

## Debugging Something

- Analyse some broken program with GDB
- Utilise all of the mentioned commands
- Try out one of the custom GDB configs
- Try out a GDB front-end (your IDE, DDD, KDbg, …)

## Setting up a Build System

- Take a small Java project and write a Makefile building the project
- The final result should be a runnable JAR file
- Add support for unit tests `make test`
- *Hint:* Took me 40 lines of code

## Profile Conway's Game of Life

- Given you already did the previous exercise
- Try out Google Performance Tools + kcachegrind

## Reading Material

- Some GDB tutorial
- [GNU Make Manual](https://www.gnu.org/software/make/manual/make.html)
- [Clang-Format documentation](https://clang.llvm.org/docs/ClangFormat.html)
