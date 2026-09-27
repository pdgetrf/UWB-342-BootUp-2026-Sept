# CSS 342 Boot Up: Linux and C++

## Session Recording

[Linux session 9/26](https://youtu.be/fZ_xXeXgb-E)

This companion keeps commands short, safe, and ready to copy and paste. Replace text in `<angle brackets>` with the appropriate values. A command beginning with `$` is a terminal command; copy the text **after** the `$`.

## 1. Mac: Hello, World!

Open **Terminal**, make a folder for today, and enter it:

```bash
mkdir -p ~/css342-bootup
cd ~/css342-bootup
```

Create `hello.cpp` in an editor and paste:

```cpp
#include <iostream>

int main() {
    std::cout << "Hello, CSS 342!\n";
    return 0;
}
```

Compile and run it. On a Mac, `clang++` is normally available with the Xcode Command Line Tools.

```bash
clang++ -std=c++17 -Wall -Wextra hello.cpp -o hello
./hello
```

If macOS says the compiler is missing, install the command-line tools, then run the compile command again:

```bash
xcode-select --install
```

## 2. AWS / Ubuntu setup

In AWS, launch an Ubuntu instance approved for the course. During setup, download and keep the key file (`.pem`) private. Do not commit it or share it.

Move the downloaded key into `~/.ssh` and restrict its permissions. Substitute the actual downloaded filename.

```bash
mkdir -p ~/.ssh
mv ~/Downloads/<your-key>.pem ~/.ssh/
chmod 400 ~/.ssh/<your-key>.pem
```

Find the instance's **Public IPv4 DNS** or **Public IPv4 address** in the AWS console. The usual Ubuntu login name is `ubuntu`.

```bash
ssh -i ~/.ssh/<your-key>.pem ubuntu@<public-ip-or-dns>
```

On the Ubuntu machine, update package information and install the C++ compiler and Git:

```bash
sudo apt update
sudo apt install -y build-essential git
g++ --version
git --version
```

Leave the server when finished:

```bash
exit
```

## 3. SSH: connect again

From a **local** terminal (your Mac), connect to the server:

```bash
ssh -i ~/.ssh/<your-key>.pem ubuntu@<public-ip-or-dns>
```

Useful check once connected:

```bash
whoami
hostname
pwd
```

Tip: a terminal running SSH is a shell on the remote machine. A new local terminal is still on your Mac.

## 4. Filesystem navigation

```bash
pwd                 # show the current directory
ls                  # list files
ls -la              # include hidden files and details
cd ~                # go to your home directory
cd ~/css342-bootup  # go to a specific directory
cd ..               # go up one directory
mkdir -p practice/week1
cd practice/week1
```

Use `Tab` to complete names instead of retyping paths. Before editing, deleting, or compiling, run `pwd` and `ls` so you know where you are.

## 5. Create, view, copy, and move files

```bash
touch notes.txt                 # create an empty file (or update its timestamp)
printf 'CSS 342 Boot Up\n' > notes.txt
cat notes.txt                   # print a small text file
less notes.txt                  # view; press q to quit
cp notes.txt notes-copy.txt     # copy a file
mv notes-copy.txt renamed.txt   # rename (or move) a file
```

`>` replaces a file's contents. Use `>>` to add at the end instead:

```bash
printf 'second line\n' >> notes.txt
```

## 6. `rm` safety

`rm` does not put files in the Trash. Start by listing the exact target:

```bash
ls -l renamed.txt
rm -i renamed.txt
```

The `-i` asks for confirmation. Type `y` only after reading the full filename. Avoid `rm -rf`, wildcards such as `rm *`, and commands we do not fully understand, especially on a server.

To remove an empty directory only:

```bash
rmdir empty-folder
```

## 7. Identify a file with `file`

The filename extension is a hint; `file` examines the contents.

```bash
file hello.cpp
file hello
file ~/.ssh/<your-key>.pem
```

## 8. Copy files with `scp`

Run these from your **Mac**, not from the SSH session.

Copy a local source file to the Ubuntu home directory:

```bash
scp -i ~/.ssh/<your-key>.pem hello.cpp ubuntu@<public-ip-or-dns>:~
```

Copy a remote file back to the Mac's current folder:

```bash
scp -i ~/.ssh/<your-key>.pem ubuntu@<public-ip-or-dns>:~/hello.cpp .
```

Use `scp -r` only when you intentionally mean to copy a directory.

## 9. Git: clone, add, commit, push

Set your identity once on each machine where you make commits. Use the email associated with your Git hosting account.

```bash
git config --global user.name "Your Name"
git config --global user.email "you@example.com"
```

Clone a repository, enter it, and inspect its status:

```bash
git clone <repository-url>
cd <repository-folder>
git status
```

After editing a file, make a small, descriptive commit:

```bash
git add hello.cpp
git status
git commit -m "Add Hello World program"
git push
```

Before beginning new work, get classmates' or your earlier changes:

```bash
git pull
```

Check what will be committed with `git status` and `git diff` before `git add`. Do **not** add private keys, passwords, or `.env` files. A minimal `.gitignore` for C++ can be:

```gitignore
hello
*.o
```

## 10. Vim basics

Open or create a file:

```bash
vim hello.cpp
```

Vim has modes. Press `Esc` to return to Normal mode before using commands below.

| Goal | Keys to press |
| --- | --- |
| Start inserting text | `i` |
| Save | `Esc`, then `:w`, then `Enter` |
| Quit | `Esc`, then `:q`, then `Enter` |
| Save and quit | `Esc`, then `:wq`, then `Enter` |
| Quit without saving | `Esc`, then `:q!`, then `Enter` |
| Search | `/word`, then `Enter`; `n` for next match |
| Undo | `u` |
| Redo | `Ctrl-r` |

Open a second file in a horizontal split:

```vim
:split other.cpp
```

Open it in a vertical split:

```vim
:vsplit other.cpp
```

Move between split panes with `Ctrl-w` followed by an arrow key (or `h`, `j`, `k`, `l`). Close the current pane with `:q`.

### Ctrl-Z: suspend and return

From Normal mode, `Ctrl-Z` suspends Vim and returns you to the shell. It does **not** quit Vim. Return to it with:

```bash
fg
```

If multiple jobs are suspended, list them first:

```bash
jobs
fg %1
```

## 11. Compile and run with `g++` (Ubuntu)

On Ubuntu, inside the folder containing `hello.cpp`:

```bash
g++ -std=c++17 -Wall -Wextra hello.cpp -o hello
./hello
```

The first command turns C++ source into an executable named `hello`; the second runs it. `-Wall -Wextra` asks for useful warnings. Recompile after changing source code.

## 12. Two-file Hello World: compile, link, run

This is the running example for compilation, linking, and `make`. It has exactly two C++ source files: `main.cpp` contains `main`; `hello.cpp` contains the `hello()` function.

`main.cpp`

```cpp
void hello();  // declaration: the function exists in another file

int main() {
    hello();
    return 0;
}
```

`hello.cpp`

```cpp
#include <iostream>

void hello() {  // definition: the actual function body
    std::cout << "Hello, CSS 342!\n";
}
```

### Step 1: compile each source file

`-c` means “compile, but do not link yet.” Each command produces an object file (`.o`).

```bash
g++ -std=c++17 -Wall -Wextra -c main.cpp -o main.o
g++ -std=c++17 -Wall -Wextra -c hello.cpp -o hello.o
ls -l main.o hello.o
```

### Step 2: link the object files

The linker combines `main.o` and `hello.o` into one executable named `hello-program`.

```bash
g++ main.o hello.o -o hello-program
./hello-program
```

For a small project, this shorter command compiles **and** links in one step. The two-step version above makes the stages visible.

```bash
g++ -std=c++17 -Wall -Wextra main.cpp hello.cpp -o hello-program
./hello-program
```

## 13. Compiler errors vs. linker errors

A **compiler error** means one source file could not be translated: a syntax mistake, missing semicolon, unknown name, or bad type. Fix the named source file and line, then compile again.

```text
main.cpp:5: error: expected ';' after expression
```

A **linker error** happens after compilation: the program needs a function or variable definition that was not included in the final executable.

```text
undefined reference to `hello()'
```

For the two-file Hello World, a likely cause is omitting `hello.o` from the linking command. Fix it by linking both object files:

```bash
g++ main.o hello.o -o hello-program
```

## 14. A simple Makefile

Create a file named exactly `Makefile` beside `main.cpp` and `hello.cpp`. The indent before each command must be a **real Tab**, not spaces.

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra

hello-program: main.o hello.o
	$(CXX) main.o hello.o -o hello-program

main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

hello.o: hello.cpp
	$(CXX) $(CXXFLAGS) -c hello.cpp -o hello.o

.PHONY: run check clean

run: hello-program
	./hello-program

check: run
	valgrind --leak-check=full --error-exitcode=1 ./hello-program

clean:
	rm -i main.o hello.o hello-program
```

`.PHONY` tells `make` that `run`, `check`, and `clean` are action names, not files it is trying to create. This matters if a file named `run`, `check`, or `clean` happens to exist: `make run` should still run the program.

Build and run:

```bash
make
./hello-program
```

Run the program through the Makefile:

```bash
make run
```

On Ubuntu, install Valgrind once if needed:

```bash
sudo apt install -y valgrind
```

Then use `make check`. It first runs the `run` target, then runs the executable under Valgrind. `--error-exitcode=1` makes the command report failure when Valgrind finds an error.

```bash
make check
```

After changing only `hello.cpp`, `make` recompiles `hello.cpp`, then links the updated program. To clean up the example, use the intentionally interactive target:

```bash
make clean
```

## Quick check before leaving

```bash
pwd
git status
make
./hello-program
```

If something behaves unexpectedly, copy the exact command and the complete error message into your notes before changing anything.
