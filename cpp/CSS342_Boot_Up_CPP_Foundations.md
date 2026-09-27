# CSS 342 Boot Up: C++ Foundations

Welcome to the CSS 342 C++ boot-up session. This handout is for you to read, run, and modify. Every code block is intentionally small and runnable: copy one stage at a time, predict what will happen, then test your prediction.

## Before you begin

Use a Linux terminal with a C++ compiler. The examples below use `g++` and C++17.

```bash
g++ --version
mkdir -p css342-bootup && cd css342-bootup
```

> **Safety:** Only run the OOM exercise on a disposable course VM. It is deliberately limited below. Never run an unlimited allocator on a shared or personal machine.

---

## 1. Testing mindset: `findMax` and TDD

**Idea:** A passing test proves only that the program works for that test. It does not prove the program is correct. We own the quality of our code, so we add cases that try to break our assumptions.

### Warm-up: max of two values

```cpp
int maxOfTwo(int a, int b) {
    return (a > b) ? a : b;
}
```

### Stage 0: begin with a JUnit-style test

This is a tiny, self-contained simulation of the JUnit experience: named tests, an assertion helper, and a pass/fail runner. It deliberately uses only free functions; the class section comes later. The important pattern in every test is: calculate an **actual** value, state the **expected** value, compare them, and show both values when they differ. It is not a replacement for a production framework such as GoogleTest.

Create `find_max.cpp` with these test functions. It should fail to compile because `findMax` does not exist yet. A real TDD cycle begins with a failure.

```cpp
#include <functional>
#include <iostream>
#include <stdexcept>
#include <string>

int passed = 0;
int failed = 0;

void expectEqual(const std::string& description, int expected, int actual) {
    if (expected != actual) {
        throw std::runtime_error(
            description + "\n"
            "  Expected: " + std::to_string(expected) + "\n"
            "  Actual:   " + std::to_string(actual));
    }
}

void runTest(const std::string& name, const std::function<void()>& test) {
    try {
        test();
        ++passed;
        std::cout << "[PASS] " << name << '\n';
    } catch (const std::exception& error) {
        ++failed;
        std::cout << "[FAIL] " << name << ": " << error.what() << '\n';
    }
}

void testFindMaxWhenFirstElementIsLargest() {
    int values[] = {9, 4, 2};
    int expected = 9;
    int actual = findMax(values, 3); // findMax does not exist yet
    expectEqual("maximum should be the first element", expected, actual);
}

int main() {
    runTest("findMax_whenFirstElementIsLargest_returnsFirstElement",
            testFindMaxWhenFirstElementIsLargest);
    std::cout << "\n" << passed << " passed, " << failed << " failed\n";
    return failed == 0 ? 0 : 1;
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max
```

### Stage 1: minimum implementation that passes one test

Now add this function above `testFindMaxWhenFirstElementIsLargest`. It passes the single named test—but it is not a correct maximum function.

```cpp
int findMax(const int values[], int size) {
    return values[0];
}
```

```bash
g++ -std=c++17 -Wall -Wextra -g find_max.cpp -o find_max && ./find_max
```

You should see a `[PASS]` line followed by `1 passed, 0 failed`. Are you done? No—the only test placed the maximum first.

### Stage 2: expose the hidden defect

Add this test function above `main`:

```cpp
void testFindMaxWhenLaterElementIsLargest() {
    int laterIsMax[] = {2, 9, 4};
    int expected = 9;
    int actual = findMax(laterIsMax, 3);
    expectEqual("maximum should be a later element", expected, actual);
}
```

Then add this call in `main()` immediately after the first `runTest(...)` call:

```cpp
runTest("findMax_whenLaterElementIsLargest_returnsLaterElement",
        testFindMaxWhenLaterElementIsLargest);
```

Run the suite again. One named test passes; the new one fails.

The failure should include enough information to diagnose the problem without opening a debugger:

```text
[FAIL] findMax_whenLaterElementIsLargest_returnsLaterElement: maximum should be a later element
  Expected: 9
  Actual:   2
```

### Stage 3: debug before fixing

Compile with `-g`, then use `gdb` (Linux):

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

The first call receives `{9, 4, 2}`; the second receives `{2, 9, 4}`. The function never examines the later elements. Before changing the code, add edge cases. Add these test functions above `main`:

```cpp
void testFindMaxWhenAllValuesAreNegative() {
    int negatives[] = {-8, -2, -5};
    int expected = -2;
    int actual = findMax(negatives, 3);
    expectEqual("maximum should be the least-negative value", expected, actual);
}

void testFindMaxWhenOneValue() {
    int oneValue[] = {42};
    int expected = 42;
    int actual = findMax(oneValue, 1);
    expectEqual("one value should be its own maximum", expected, actual);
}
```

Also add both calls in `main()`:

```cpp
runTest("findMax_whenAllValuesAreNegative_returnsLeastNegative",
        testFindMaxWhenAllValuesAreNegative);
runTest("findMax_whenOneValue_returnsThatValue",
        testFindMaxWhenOneValue);
```

### Stage 4: correct implementation

Replace the temporary implementation. The precondition is `size > 0`.

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

## 2. Baby-step coding

### `const`: name values that should not change

Use `const` when a value is set once and should not be reassigned. It documents your intent and lets the compiler catch accidental changes.

```cpp
#include <iostream>

int main() {
    const int daysInMonth = 30;
    const double annualRate = 0.08;
    double balance = 1000.0;

    balance += 500.0; // allowed: balance can change
    std::cout << "Balance: $" << balance << '\n';
    std::cout << "Days: " << daysInMonth << '\n';

    // daysInMonth = 31; // compiler error: a const value cannot change
}
```

Use `const` for fixed facts such as a target amount, an interest rate, or a number of days. Do not use it for values that are expected to change during a calculation, such as `balance`, `months`, or a loop counter.

### Exercise A: $1,000,000 now or a penny that doubles?

Predict first: would you take $1,000,000 today, or one penny tomorrow that doubles every day for 30 days? The final day matters—watch for off-by-one errors.

```cpp
#include <iomanip>
#include <iostream>

int main() {
    long double pennies = 1.0L;

    for (int day = 1; day <= 30; ++day) {
        std::cout << "Day " << std::setw(2) << day
                  << ": $" << std::fixed << std::setprecision(2)
                  << static_cast<double>(pennies / 100.0L) << '\n';
        pennies *= 2.0L;
    }

    const long double doubledChoice = pennies / 2.0L / 100.0L;
    std::cout << "Final doubled amount: $"
              << static_cast<double>(doubledChoice) << '\n';
    std::cout << (doubledChoice > 1000000.0L
                      ? "Choose the doubling penny.\n"
                      : "Choose the $1,000,000.\n");
}
```

```bash
g++ -std=c++17 -Wall -Wextra penny.cpp -o penny && ./penny
```

Try these deliberate changes:

- Change `day <= 30` to `day < 30`. What changed, and why?
- Try `int pennies = 1;`. Why is that a poor model for dollars and cents here?
- Change 30 to 31 and predict the result before running.

### Exercise B: savings to $1,000,000

This model applies a monthly deposit, then one month of interest. State that assumption clearly: changing the order changes the result.

```cpp
#include <iomanip>
#include <iostream>

int main() {
    const double target = 1000000.0;
    double balance = 1000.0;
    const double monthlyDeposit = 500.0;
    const double annualRate = 0.08;
    int months = 0;

    while (balance < target) {
        balance += monthlyDeposit;
        balance *= 1.0 + annualRate / 12.0;
        ++months;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "Balance: $" << balance << '\n';
    std::cout << "Months: " << months << '\n';
    std::cout << "Years: " << months / 12.0 << '\n';
}
```

Before running it, predict the result for `$50`, `$500`, and `$1,000` monthly deposits. Then refactor: keep the behavior the same while moving the calculation into a reusable function.

```cpp
#include <iostream>

double yearsToMillion(double startingBalance,
                      double monthlyDeposit,
                      double annualRate) {
    const double target = 1000000.0;
    double balance = startingBalance;
    int months = 0;

    while (balance < target) {
        balance += monthlyDeposit;
        balance *= 1.0 + annualRate / 12.0;
        ++months;
    }

    return months / 12.0;
}

int main() {
    std::cout << "At $50/month:  " << yearsToMillion(1000, 50, 0.08) << " years\n";
    std::cout << "At $500/month: " << yearsToMillion(1000, 500, 0.08) << " years\n";
}
```

---

## 3. Memory: stack, heap, pointers, arrays, and ownership

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

In modern production C++, prefer `std::vector`, `std::string`, and smart pointers. We use raw `new`/`delete` here to make ownership and lifetime visible.

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

Run this only on a disposable Linux course VM. It uses `systemd-run` to cap the demo process at 256 MiB, so you can observe an allocation failure without exhausting the host.

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

If `systemd-run --user` is unavailable on your VM, do not remove the limit and run the demo without one. Ask the course staff or VM administrator for a cgroup/container limit instead.

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

## 4. OOP: from Java `ArrayList` to a C++ dynamic array

In Java, `ArrayList` grows for us:

```java
ArrayList<Integer> scores = new ArrayList<>();
scores.add(10);
scores.add(20);
scores.add(30);
System.out.println(scores.get(1));
```

It still uses an underlying array with a capacity. When it fills, the implementation allocates a larger array, copies elements, and releases the old array for garbage collection. In C++, you will make those steps visible.

### Simplified `DynamicIntArray`

This class owns its buffer. It starts with capacity 2, doubles when full, copies values, deletes the old buffer, and releases the final buffer in its destructor. Read the ownership flow as you run the program.

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
