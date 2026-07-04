# libctools

A lightweight, dual-purpose C utility framework supporting both standard PC architectures and resource-constrained embedded systems.

---

## Key Features

* **Unified Header Routing** — Automatically detects the target environment via the `EMBEDDED` macro and routes to the appropriate sub-header.
* **Thread-safe I/O Utilities** — Provides standard I/O logging primitives such as `println` designed for safe, predictable output.

---

## Installation

Build the static libraries:
```bash
make

Install system-wide (requires root privileges):
Bash

sudo make install

    Note: Headers are installed flatly into /usr/local/include/ and static archives are stored in /usr/local/lib/.

Usage Example
C

#include <libctools.h>

int main(void)
{
    println("Hello from libctools!");
    return 0;
}

Compilation

Compile your program against the installed library cleanly:
Bash

gcc -o my_program main.c -lctools

For embedded targets, define the EMBEDDED macro during compilation:
Bash

gcc -DEMBEDDED -o my_program main.c -lctools

Author: x0rkr


Developed and maintained by x0rkr