# CSS 342 Boot Up: C++ Foundations

Welcome to the CSS 342 C++ boot-up session. We will read, run, and modify small examples together. Copy one stage at a time, predict the outcome, and then test that prediction.

## Guide: TL;DR

- [Development environment](#0-development-environment): Choose a Windows, macOS, or Ubuntu Linux setup; use CLion for editing and debugging, and Linux for `g++` and Valgrind.
- [Before we begin](#before-we-begin): Check that `g++` is available and create a working folder.
- [Baby-step coding](#1-baby-step-coding-start-by-writing-code): Start coding immediately with loops, numeric types, conditionals, and functions through two financial exercises; see the short `const` appendix afterward.
- [Memory](#2-memory-stack-heap-pointers-arrays-and-ownership): Learn bits, bytes, addresses, stack versus heap, pointers, references, arrays, dynamic allocation, leaks, Valgrind, and controlled OOM behavior.
- [Testing mindset](#3-testing-mindset-findmax-and-tdd): Build evidence with tests, follow a TDD cycle, turn a bug report into a failing test, and use CLion to investigate a `findMax` bug.
- [OOP and dynamic arrays](#4-oop-from-java-arraylist-to-a-c-dynamic-array): Connect Java `ArrayList` to a C++ class that owns, grows, and releases a dynamic array.
- [Exit ticket](#exit-ticket): Check the core ideas before leaving the session.

## 0. Development environment

We can write C++ on Windows, macOS, or Linux. The goal is the same on every platform: an editor or IDE, a compiler, and a debugger. During this session, we use **CLion** to write code and step through it with breakpoints. We also use **Ubuntu Linux** for the command-line compiler and Valgrind memory-leak checks.

CLion runs on Windows, macOS, and Linux. It supports CMake projects and can use GCC, Clang, MSVC, MinGW, and WSL toolchains. See the official [CLion quick-start guide](https://www.jetbrains.com/help/clion/clion-quick-start-guide.html) for installation and toolchain details.

### Why we use CLion

We use CLion because it offers a free non-commercial license, and JetBrains also has complimentary access programs for eligible students and teachers. Check the current license terms when activating it. It gives us the same editor and debugger experience on Windows and macOS, and it also runs on Linux. For Linux, JetBrains supports installation through Toolbox, a downloaded archive, or Ubuntu's Snap package. We have not used CLion on Linux in this session, but it is a supported option.

CLion comes from JetBrains, the company behind IntelliJ IDEA. If we have used IntelliJ before, the project navigation, code completion, refactoring, run configurations, and debugging workflow will feel familiar. Those development tools let us spend more time understanding C++ behavior and less time managing editor details.

### Choose a platform

| Platform | Good starting tools | Quick setup | Course use |
| --- | --- | --- | --- |
| Windows | CLion with its bundled MinGW toolchain, or Visual Studio with the **Desktop development with C++** workload | Install CLion through [JetBrains Toolbox](https://www.jetbrains.com/toolbox-app/) and confirm a toolchain in CLion. Windows students can also use Ubuntu through WSL for a Linux environment. | Write and debug in CLion. Use the course Ubuntu machine or WSL when Linux tools are needed. |
| macOS | CLion plus Apple's command-line developer tools | Run `xcode-select --install`, then open CLion and let it detect the Clang toolchain. | Write and debug in CLion. Use the course Ubuntu machine for the Linux and Valgrind exercises. |
| Linux, using Ubuntu | CLion or another editor, `g++`, `gdb`, and Valgrind | Install the tools with the commands below. | This is the environment we use for `g++` compilation and Valgrind. |

Other common IDE choices include Visual Studio on Windows and VS Code on all three platforms. Use the environment that lets us edit, build, run, and debug C++ comfortably. CLion is the shared debugger demonstration environment for this session.

### Ubuntu setup for this session

On an Ubuntu machine, install the compiler, debugger, build tools, and Valgrind:

```bash
# Refresh Ubuntu's list of available packages.
sudo apt update

# Install the C++ compiler and build tools, terminal debugger, memory checker,
# CMake build system, and Vim editor.
sudo apt install -y build-essential gdb valgrind cmake vim

# Confirm that the compiler, debugger, and memory checker are ready to use.
g++ --version
gdb --version
valgrind --version
```

`build-essential` installs the GCC C++ toolchain, including `g++` and `make`. Valgrind is a Linux memory-analysis tool that we use later to find leaks and invalid memory use.

### Vim on Linux

Vim is a strong development tool, not just a text editor. It is fast, available on many Linux systems, and practical when we connect to a remote machine where a graphical IDE is unavailable. We can edit source files, search, replace text, and work efficiently without leaving the terminal.

From the instructor's perspective, Vim is worth learning beyond this class. We do not need to master every command today, but becoming comfortable with it will help when working on servers, in remote environments, and throughout a software-development career.

### CLion and Linux: how we use both

For ordinary coding, we create a C++ project in CLion, write code, and use breakpoints, Step Into, and Step Over to debug. CLion works locally on Windows, macOS, and Linux. When we need Linux-specific tools, we compile and run on Ubuntu. Windows users may use WSL, and any student may use the course Linux machine if one is provided.

## Before we begin

For the command-line examples, use an Ubuntu terminal with a C++ compiler. The examples below use `g++` and C++17.

```bash
g++ --version
mkdir -p css342-bootup && cd css342-bootup
```

---

## 1. Baby-step coding: start by writing code

We start by writing a small program right away. This gives us a feel for the C++ tools, variables, loops, output, and functions. Once we have code in front of us, we can ask the next important question: how do we know it works?

### Exercise A: $1,000,000 now or a penny that doubles?

Before we run the program, choose: $1,000,000 today, or one penny tomorrow that doubles every day for 30 days? The final day matters. Count how many times the loop actually runs before changing anything.

Create a file named `penny_doubling.cpp`, then copy this starter code into your coding environment:

```cpp
#include <iomanip>
#include <iostream>

int main() {
    // Imagine a strange offer: take $1,000,000 today, or take one penny
    // tomorrow and let it double every day for 30 days. At first, a penny
    // sounds tiny. For example, after a few doublings it is 1, 2, 4, 8...
    // Does the small choice ever catch the $1,000,000 choice?
    //
    // TODO: Build the simulation. Start with one penny, double it once per
    // day, print each day's dollar amount, then announce which choice wins.
    //
    // Hints as we build it:
    // - Use long double for the number of pennies, starting at 1.0L.
    // - A for loop can count the days. Be careful: if we count from 0 through
    //   30, how many loop iterations do we actually run?
    // - Divide pennies by 100.0L to display dollars, such as $0.01 for one penny.
    // - Use std::fixed and std::setprecision(2) to make dollar amounts readable.
    // - Use an if/else statement or the ternary operator to announce the winner.
}
```

```bash
g++ -std=c++17 -Wall -Wextra penny_doubling.cpp -o penny_doubling && ./penny_doubling
```

Try these deliberate checks:

- Count the loop iterations from `day = 0` through `day = 30`. Does that represent 30 days or 31 days?
- Fix the bounds so the code models exactly 30 days. Explain why the revised starting value and condition are correct.
- Try `int pennies = 1;`. Why is that a poor model for dollars and cents here?

### Completed reference file

After attempting the exercise, compare your work with [penny_doubling.cpp](penny_doubling.cpp). It compiles directly with the command above.

### Exercise B: savings to $1,000,000

While we are on the topic of $1,000,000, here is the next question: **how soon can we get there?** This model compounds **annually**, not monthly. Each year, we apply 7% interest to the previous year's ending balance, then add 12 months of new contributions. We also compare the account's value with the amount of money we personally contributed. We use a **7% annual rate** as a conservative classroom estimate based on the S&P 500, an index of roughly 500 large U.S. companies. We can change the starting deposit, monthly contribution, rate, and target when running the example.

> **Teaching only, not investment advice:** This is a programming model, not a recommendation, prediction, or guarantee about investing. Real investment returns vary, and past market performance does not guarantee future results.

Use the [Exercise B compounding-interest reference](exercise_b.pdf) alongside this coding exercise for the underlying financial model and example calculation.

Create `savings_to_million.cpp`, then copy this starter into your coding environment:

```cpp
#include <iomanip>
#include <iostream>

int main() {
    // Imagine that future-you has a simple plan: start with some savings,
    // add money every month, and let the account earn interest. The target is
    // $1,000,000. How long will the plan take?
    //
    // Compounding means that interest is calculated from the current balance,
    // including interest earned in earlier years. In other words, the money
    // starts helping to earn more money. A small monthly habit can matter.
    //
    // TODO: Simulate the account one year at a time. Start with an initial
    // deposit, monthly contribution, annual interest rate, and target. For
    // this example, use 7.0 as the annual percentage rate: a conservative
    // classroom estimate based on the S&P 500, an index of roughly 500 large
    // U.S. companies. Keep going until the balance reaches the target.
    //
    // Hints as we build it:
    // - Use double for initialDeposit, monthlyContribution,
    //   annualInterestRate, invested, total, and target. Try changing the
    //   7.0 rate or monthly contribution after the first run.
    // - Use an int named years to count full years.
    // - A for loop fits: keep looping while balance is below the target, and
    //   increase years once after each completed year.
    // - Start invested and total at initialDeposit.
    // - At the end of each year, calculate total with the same pattern:
    //   total = total * (1 + annualInterestRate / 100.0)
    //         + monthlyContribution * 12;
    // - Add monthlyContribution * 12 to invested, then print the year,
    //   total value, and invested amount so we can compare them.
    // - When the loop ends, print how many years it took. Use an if statement
    //   to announce when total has reached $1M.
}
```

```bash
g++ -std=c++17 -Wall -Wextra savings_to_million.cpp -o savings_to_million && ./savings_to_million
```

### Completed reference file: savings_to_million.cpp

After attempting the simulation, compare your work with [savings_to_million.cpp](savings_to_million.cpp). This is the completed first version, before we refactor the calculation into a function.

### Refactor the calculation into a function

Now predict the result for `$50`, `$500`, and `$1,000` monthly deposits. Then refactor: keep the behavior the same while moving the calculation into a reusable function.

```cpp
#include <iostream>

int yearsToMillion(double initialDeposit,
                   double monthlyContribution,
                   double annualInterestRate) {
    const double target = 1000000.0;
    double total = initialDeposit;
    int years = 0;

    for (; total < target; ++years) {
        total = total * (1.0 + annualInterestRate / 100.0)
              + monthlyContribution * 12;
    }

    return years;
}

int main() {
    std::cout << "At $50/month:  " << yearsToMillion(500, 50, 7.0) << " years\n";
    std::cout << "At $500/month: " << yearsToMillion(500, 500, 7.0) << " years\n";
}
```

### Appendix: `const`

We use `const` when a value is set once and should not be reassigned. It documents intent and lets the compiler catch accidental changes.

```cpp
#include <iostream>

int main() {
    const int daysInMonth = 30;
    const double annualRate = 7.0;
    double balance = 1000.0;

    balance += 500.0; // allowed: balance can change
    std::cout << "Balance: $" << balance << '\n';
    std::cout << "Days: " << daysInMonth << '\n';

    // daysInMonth = 31; // compiler error: a const value cannot change
}
```

Use `const` for fixed facts such as a target amount, an interest rate, or a number of days. Do not use it for values that are expected to change during a calculation, such as `balance`, `years`, or a loop counter.

### From writing code to memory

We have started writing code. Next, we look at where its values live and how C++ lets us work with memory.

---


## 2. Memory: stack, heap, pointers, arrays, and ownership

Use the [memory system reference](memory_system.pdf) alongside this section. It provides a visual companion for the memory concepts and terminology we use below.

### Memory foundations: bits, bytes, size, and addresses

A computer stores information as **bits**: each bit is a `0` or a `1`. Eight bits make one **byte**. Memory is measured in larger groups of bytes:

- `1 byte` = 8 bits
- `1 KiB` = 1,024 bytes
- `1 MiB` = 1,024 KiB = 1,048,576 bytes
- `1 MB` is often used informally for about one million bytes; system tools may display either MB or MiB, so read the label.

Think of memory as a very long street of mailboxes.

- A mailbox's **address** tells you where it is, like a house number.
- Its **contents** are the bits stored there, such as the value of an `int`.
- Its **size** tells you how many neighboring mailboxes the value occupies. For example, `sizeof(int)` is commonly 4 bytes, but verify rather than assume.

```cpp
#include <iostream>

int main() {
    int score = 342;

    std::cout << "contents: " << score << '\n';
    std::cout << "address:  " << &score << '\n';
    std::cout << "size:     " << sizeof(score) << " bytes\n";
}
```

The address will differ each time we run the program. A pointer stores an address: it is like writing a mailbox's house number on a piece of paper so we can find that mailbox again.

### Stack versus heap

Local variables and function-call bookkeeping live on the **stack** and are released automatically when their scope ends. Dynamically allocated objects live on the **heap** until code releases them (or the process ends).

```cpp
#include <iostream>

int main() {
    int stackValue = 7;           // automatic storage; stack
    int* heapValue = new int(42); // dynamic storage; heap

    std::cout << stackValue << ", " << *heapValue << '\n';
    delete heapValue;             // release exactly once
    heapValue = nullptr;          // avoid a dangling pointer
}
```

### Recursive stack-overflow demonstration

This intentionally crashes after a machine-dependent number of calls. Compile with `-O0` so the compiler does not optimize away the recursive frame.

```cpp
#include <cstddef>
#include <iostream>

void useStack(std::size_t depth) {
    volatile char oneMiB[1024 * 1024]{}; // force roughly 1 MiB per call
    oneMiB[0] = static_cast<char>(depth);
    std::cout << "depth = " << depth << std::endl;
    useStack(depth + 1);
}

int main() {
    useStack(1);
}
```

```bash
ulimit -s
g++ -std=c++17 -O0 -g stack_overflow.cpp -o stack_overflow
./stack_overflow
```

The exact depth varies with stack limits, OS, compiler, architecture, and debug settings. The point is that recursion consumes a new stack frame per call; it is not an infinite memory source.

### Pointers versus references; pass by pointer/reference

```cpp
#include <iostream>

void addTenByPointer(int* value) {
    if (value != nullptr) { // pointer can be null
        *value += 10;
    }
}

void addTenByReference(int& value) {
    value += 10;            // reference is an alias for an existing object
}

void printByReference(const int& value) {
    std::cout << value << '\n'; // const: read only, no copy
}

int main() {
    int score = 5;
    int* pointer = &score;
    int& reference = score;

    *pointer = 6;
    reference = 7;
    addTenByPointer(&score);
    addTenByReference(score);
    printByReference(score); // 27
}
```

Use a pointer when “no object” is a meaningful possibility or when pointer syntax is part of the interface. Prefer a reference when the function requires a valid object and simply needs an alias.

### Arrays and pointer decay

```cpp
#include <iostream>

void printAll(const int values[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int values[] = {10, 20, 30, 40};

    std::cout << values[2] << '\n';       // 30
    std::cout << *(values + 2) << '\n';   // also 30
    std::cout << values << '\n';          // address of first element in most expressions

    printAll(values, 4);
}
```

An array is not literally a pointer, but in most expressions its name **decays** to a pointer to its first element. Pointer arithmetic advances in units of the pointed-to type: `values + 2` points two `int` elements later.

### Out of bounds is undefined behavior

```cpp
#include <iostream>

int main() {
    int values[] = {10, 20, 30};
    std::cout << values[3] << '\n'; // undefined behavior: do not rely on any result
}
```

C++ does not provide Java-style bounds checks for built-in arrays. It may print a surprising value, appear to work, crash, or corrupt unrelated data. None is valid behavior to depend on.

### `new[]` and `delete[]`

The form of deletion must match the allocation form.

```cpp
#include <iostream>

int main() {
    const int size = 4;
    int* values = new int[size]{10, 20, 30, 40};

    for (int i = 0; i < size; ++i) {
        std::cout << values[i] << ' ';
    }
    std::cout << '\n';

    delete[] values; // new[] pairs with delete[]
    values = nullptr;
}
```

Pairing rules:

- `new T` → `delete pointer`
- `new T[n]` → `delete[] pointer`

In modern C++, we usually prefer `std::vector`, `std::string`, and smart pointers. We use raw `new`/`delete` here to make ownership and lifetime visible.

### Memory leak and Valgrind

`leak.cpp` deliberately leaks memory:

```cpp
int main() {
    int* forgotten = new int[100];
    forgotten[0] = 42;
    // delete[] forgotten;  // intentionally omitted
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g leak.cpp -o leak
valgrind --leak-check=full --show-leak-kinds=all ./leak
```

Fix it by adding:

```cpp
delete[] forgotten;
forgotten = nullptr;
```

Run Valgrind again. The goal is no definitely-lost blocks. The operating system generally reclaims process memory when a program exits, but a leak is dangerous for long-running programs: it accumulates while the process is alive, increases memory pressure, slows systems, and can cause failures or OOM termination.

### Controlled OOM demonstration with tmux

> **Safety:** Only run this exercise on a disposable course VM. It is deliberately limited below. Never run an unlimited allocator on a shared or personal machine.

This uses `systemd-run` to cap the demo process at 256 MiB, so we can observe an allocation failure without exhausting the host.

`oom_demo.cpp`:

```cpp
#include <chrono>
#include <cstddef>
#include <exception>
#include <iostream>
#include <thread>
#include <vector>

int main() {
    constexpr std::size_t chunkMiB = 16;
    constexpr std::size_t chunkBytes = chunkMiB * 1024 * 1024;
    std::vector<char*> chunks;

    try {
        while (true) {
            char* chunk = new char[chunkBytes];
            for (std::size_t i = 0; i < chunkBytes; i += 4096) {
                chunk[i] = 1; // touch each page: allocation becomes real memory use
            }
            chunks.push_back(chunk);
            std::cout << "Allocated " << chunks.size() * chunkMiB << " MiB" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
    } catch (const std::bad_alloc&) {
        std::cerr << "Allocation failed: memory limit reached.\n";
    }

    for (char* chunk : chunks) {
        delete[] chunk;
    }
}
```

Compile it, then start a tmux session with three panes:

```bash
g++ -std=c++17 -O0 -g oom_demo.cpp -o oom_demo
tmux new-session -s oom-demo
```

In tmux, create panes:

```bash
# Pane 1: run the capped demo
systemd-run --user --scope -p MemoryMax=256M ./oom_demo

# Ctrl-b % creates a vertical split. In pane 2, watch host memory.
watch -n 1 free -h

# Ctrl-b " creates a horizontal split. In pane 3, observe messages when permitted.
journalctl -kf | grep -Ei 'oom|out of memory|killed process|memory'
```

Afterward, inspect the exit result and recent messages:

```bash
echo $?
journalctl -k -b | grep -Ei 'oom|out of memory|killed process|memory' | tail -n 20
tmux kill-session -t oom-demo
```

If `systemd-run --user` is unavailable on the VM, do not remove the limit and run the demo without one. Ask the course staff or VM administrator for a cgroup/container limit instead.

### Allocate/deallocate repeatedly versus preallocate and reuse

Allocation can have nontrivial and variable cost. Avoid repeatedly allocating in a time-sensitive loop when storage can be reused.

```cpp
#include <chrono>
#include <iostream>

constexpr int iterations = 100000;
constexpr int count = 1000;

int main() {
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < iterations; ++i) {
        int* values = new int[count]{};
        values[0] = i;
        delete[] values;
    }
    auto afterAllocateEachTime = std::chrono::steady_clock::now();

    int* reused = new int[count]{};
    for (int i = 0; i < iterations; ++i) {
        reused[0] = i;
    }
    delete[] reused;
    auto afterReuse = std::chrono::steady_clock::now();

    std::cout << "allocate/delete each iteration: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     afterAllocateEachTime - start).count() << " ms\n";
    std::cout << "allocate once and reuse: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(
                     afterReuse - afterAllocateEachTime).count() << " ms\n";
}
```

This is a conceptual comparison, not a rigorous benchmark. Focus on the engineering pattern: establish ownership, allocate a bounded pool when appropriate, reuse it, and release it at the end of its lifetime.

---

## 3. Testing mindset: `findMax` and TDD

### “Does it work?”

We have written a function. Someone asks: **Does it work?**

“It should” may be an initial guess, but it is not a useful final answer for a computer scientist. We need evidence.

### What testing means

A **test** runs a small, specific example and checks its result:

1. Choose an input.
2. State the result you **expect**.
3. Run the code to get the **actual** result.
4. Compare expected and actual, then report whether they match.

For example, for `findMax({9, 4, 2})`, we expect `9`. The test calls the function, compares its actual result with `9`, and reports pass or fail.

After we have tests, an evidence-based answer to “Does it work?” sounds like this:

> “It passes the tests I wrote for these cases. I may need more tests to cover other cases.”

### Our responsibility as developers

Testing is our responsibility. We do not wait for a professor's tests to tell us whether a program works. We write tests, run them, and show the evidence that the code passes them. In a class, this can feel unnecessary; on a real project, it is how teammates and reviewers gain confidence that a change did not break the software.

### Warm-up: max of two values

```cpp
int maxOfTwo(int a, int b) {
    return (a > b) ? a : b;
}
```

### Part A: test-driven development

This is a tiny, self-contained simulation of the JUnit experience: named tests, an assertion helper, and pass/fail output. It deliberately uses only free functions; the class section comes later. It is not a replacement for a production framework such as GoogleTest.

#### Stage 1: write a test first

Create `find_max.cpp` with these test functions. It should fail to compile because `findMax` does not exist yet. That failure is the first part of the TDD cycle.

```cpp
#include <iostream>
#include <string>

int passed = 0;
int failed = 0;

void expectEqual(const std::string& testName, int expected, int actual) {
    if (expected == actual) {
        ++passed;
        std::cout << "[PASS] " << testName << '\n';
    } else {
        ++failed;
        std::cout << "[FAIL] " << testName << '\n'
                  << "  Expected: " << expected << '\n'
                  << "  Actual:   " << actual << '\n';
    }
}

void testFindMaxWhenFirstElementIsLargest() {
    int values[] = {9, 4, 2};
    int expected = 9;
    int actual = findMax(values, 3); // findMax does not exist yet
    expectEqual("findMax_whenFirstElementIsLargest_returnsFirstElement",
                expected, actual);
}

int main() {
    testFindMaxWhenFirstElementIsLargest();
    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max
```

#### Stage 2: write the minimum code to pass

Now add this function above `testFindMaxWhenFirstElementIsLargest`. It passes the single named test, but it is not a correct maximum function.

```cpp
int findMax(const int values[], int size) {
    return values[0];
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max && ./find_max
```

You should see a `[PASS]` line followed by `1 passed, 0 failed`.

### What does a passing test prove?

The test proves that `findMax` works for the input `{9, 4, 2}`. It does **not** prove that `findMax` works for every valid input. Even “all tests pass” means only that all tests **currently written** pass; the test suite can still be incomplete.

That is why developers add more cases, especially cases that challenge assumptions. The next part gives the function a believable bug and shows how several passing tests can still miss it.

### Part B: passing tests can still miss a bug

Replace the minimum implementation with this version. It looks like a normal loop and is intentionally incomplete. Do not change it yet; use the tests and debugger to determine why it fails.

```cpp
int findMax(const int values[], int size) {
    int maximum = values[0];

    for (int i = 1; i < size; ++i) {
        if (values[i] > maximum) {
        }
    }
    return maximum;
}
```

#### Stage 3: add more tests that still pass

The existing first-element test still passes. Add these two tests. They also pass because in both cases the first element really is the maximum.

```cpp
void testFindMaxWhenValuesDecrease() {
    int values[] = {10, 7, 3};
    int expected = 10;
    int actual = findMax(values, 3);
    expectEqual("findMax_whenValuesDecrease_returnsFirstElement", expected, actual);
}

void testFindMaxWhenOneValue() {
    int values[] = {42};
    int expected = 42;
    int actual = findMax(values, 1);
    expectEqual("findMax_whenOneValue_returnsThatValue", expected, actual);
}
```

Add both calls in `main()`:

```cpp
testFindMaxWhenValuesDecrease();
testFindMaxWhenOneValue();
```

All three tests pass. That does **not** mean the loop is correct; it means the tests have not yet made a later value the maximum.

#### Stage 4: turn a bug report into a failing test

Imagine a teammate reports: “When I call `findMax` with `{2, 9, 4}`, it returns `2`, not `9`.”

Do **not** open the debugger yet. First, turn the report into a missing, reproducible test. This confirms that we understand the report and preserves the problem as a test that must pass after the fix.

Add this test function above `main`, using the reported input and expected result:

```cpp
void testFindMaxWhenLaterElementIsLargest() {
    int laterIsMax[] = {2, 9, 4};
    int expected = 9;
    int actual = findMax(laterIsMax, 3);
    expectEqual("findMax_whenLaterElementIsLargest_returnsLaterElement",
                expected, actual);
}
```

Then add this call in `main()` immediately after the first test call:

```cpp
testFindMaxWhenLaterElementIsLargest();
```

Run the program again. The first three tests pass, while `testFindMaxWhenLaterElementIsLargest()` fails. Now the bug report is a verified failing test, so we are ready to debug.

The failure should include enough information to diagnose the problem without opening a debugger:

```text
[FAIL] findMax_whenLaterElementIsLargest_returnsLaterElement
  Expected: 9
  Actual:   2
```

#### Stage 5: debug before fixing

##### Primary workflow: CLion breakpoints

We use CLion's debugger to see why the second test fails before changing the code.

1. Open `find_max.cpp` in CLion and make sure the loop implementation from the previous step is present.
2. Click in the left gutter beside the line `int actual = findMax(laterIsMax, 3);` to add a breakpoint.
3. Start the program with **Debug** (the bug icon), not Run.
4. When execution pauses, inspect `laterIsMax`, `expected`, and `actual` in the Variables pane. `actual` has not been assigned yet.
5. Use **Step Into** to enter `findMax`. Inspect `maximum`, `values[0]`, and `size`.
6. Use **Step Over** to move through the loop. When the code reaches `9`, watch whether `maximum` changes. From that observation, identify which statement belongs inside the `if` block.
7. Step Over the `return` statement. Back in the test, inspect `actual`: it is `2`, even though `expected` is `9`.
8. Use **Resume Program** to let the test framework report the failure.

After we write the correct loop, put a breakpoint on `if (values[i] > maximum)`. Step Over the loop and watch `i`, `values[i]`, and `maximum`. We should see `maximum` change from `2` to `9`.

##### Optional terminal workflow: `gdb`

For a Linux-terminal alternative, compile with `-g`, then use `gdb`:

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max
gdb ./find_max
```

At the `(gdb)` prompt:

```gdb
break findMax
run
print size
print values[0]
continue
print values[0]
quit
```

The first call receives `{9, 4, 2}`; the failing call receives `{2, 9, 4}`. Use the debugger observations to explain the result. Before fixing the code, add one more test that describes the same expected behavior with a different input:

```cpp
void testFindMaxWhenLargestValueIsLast() {
    int values[] = {3, 5, 10};
    int expected = 10;
    int actual = findMax(values, 3);
    expectEqual("findMax_whenLargestValueIsLast_returnsLastElement", expected, actual);
}
```

Also add this call in `main()`:

```cpp
testFindMaxWhenLargestValueIsLast();
```

#### Stage 6: fix the bug and run every test

Replace the incomplete implementation with the corrected version below. Compare it with the earlier loop and identify the line that changes the result. The precondition is `size > 0`.

```cpp
int findMax(const int values[], int size) {
    int maximum = values[0];

    for (int i = 1; i < size; ++i) {
        if (values[i] > maximum) {
            maximum = values[i];
        }
    }
    return maximum;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max && ./find_max
```

**Takeaway:** Tests are evidence, not a certificate of correctness. When a bug appears, preserve it as a new test, add nearby cases, then fix the implementation.

---

## 4. OOP: from Java `ArrayList` to a C++ dynamic array

In Java, `ArrayList` grows for us:

```java
ArrayList<Integer> scores = new ArrayList<>();
scores.add(10);
scores.add(20);
scores.add(30);
System.out.println(scores.get(1));
```

It still uses an underlying array with a capacity. When it fills, the implementation allocates a larger array, copies elements, and releases the old array for garbage collection. In C++, we make those steps visible.

### Simplified `DynamicIntArray`

This class owns its buffer. It starts with capacity 2, doubles when full, copies values, deletes the old buffer, and releases the final buffer in its destructor. Trace the ownership flow as we run the program.

```cpp
#include <cassert>
#include <iostream>

class DynamicIntArray {
public:
    DynamicIntArray()
        : data_(new int[2]), size_(0), capacity_(2) {}

    ~DynamicIntArray() {
        delete[] data_;
    }

    void add(int value) {
        if (size_ == capacity_) {
            grow();
        }
        data_[size_] = value;
        ++size_;
    }

    int get(int index) const {
        assert(index >= 0 && index < size_);
        return data_[index];
    }

    int size() const {
        return size_;
    }

    int capacity() const {
        return capacity_;
    }

private:
    void grow() {
        const int newCapacity = capacity_ * 2;
        int* larger = new int[newCapacity];

        for (int i = 0; i < size_; ++i) {
            larger[i] = data_[i];
        }

        delete[] data_;
        data_ = larger;
        capacity_ = newCapacity;
    }

    int* data_;
    int size_;
    int capacity_;
};

int main() {
    DynamicIntArray values;

    for (int value : {10, 20, 30, 40, 50}) {
        values.add(value);
        std::cout << "size=" << values.size()
                  << ", capacity=" << values.capacity() << '\n';
    }

    std::cout << values.get(2) << '\n'; // 30
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g dynamic_array.cpp -o dynamic_array
./dynamic_array
valgrind --leak-check=full ./dynamic_array
```

### Trace the growth

Start: `size = 0`, `capacity = 2`

1. Add 10 → `size = 1`, capacity remains 2.
2. Add 20 → `size = 2`, capacity remains 2.
3. Add 30 → full: allocate capacity 4, copy 10 and 20, `delete[]` the old capacity-2 buffer, then insert 30.
4. Add 40 → `size = 4`, capacity remains 4.
5. Add 50 → full again: grow to capacity 8.

**Ownership rule:** The constructor acquires `data_`; the destructor releases `data_`. That constructor/destructor partnership is the core of resource management in this example.

> This intentionally simplified class should not be copied with the compiler-generated copy constructor or copy assignment operator, because two objects would then try to delete the same buffer. Later, use `std::vector<int>` in real code or learn the Rule of Three/Five before adding copying.

---

## Exit ticket

1. Why can a program pass one `findMax` test and still be wrong?
2. Why does `values[i]` mean the same thing as `*(values + i)` for a built-in array?
3. What must pair with `new[]`?
4. Why can a memory leak be harmless after a short program exits but harmful in a server running for months?
5. In the dynamic array, what must happen before the old buffer is deleted during a grow?
